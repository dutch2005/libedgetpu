# Lint as: python3
# Copyright 2026 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests for pycoral.adapters.classify."""

import unittest
from unittest.mock import MagicMock
import numpy as np
from pycoral.adapters import classify

class TestClassify(unittest.TestCase):

  def test_get_classes_from_scores(self):
    scores = np.array([0.1, 0.5, 0.2, 0.9, 0.3], dtype=np.float32)
    
    # Test top_k=2
    results = classify.get_classes_from_scores(scores, top_k=2)
    self.assertEqual(len(results), 2)
    self.assertEqual(results[0].id, 3)
    self.assertAlmostEqual(results[0].score, 0.9)
    self.assertEqual(results[1].id, 1)
    self.assertAlmostEqual(results[1].score, 0.5)

    # Test score_threshold=0.4
    results = classify.get_classes_from_scores(scores, score_threshold=0.4)
    self.assertEqual(len(results), 2)
    self.assertEqual(results[0].id, 3)
    self.assertEqual(results[1].id, 1)

  def test_get_scores_quantized(self):
    # Mock interpreter
    interpreter = MagicMock()
    output_details = {
        'index': 0,
        'dtype': np.uint8,
        'quantization': (0.1, 128),
        'shape': [1, 5]
    }
    interpreter.get_output_details.return_value = [output_details]
    
    # Quantized data: [128, 138, 118] -> Dequantized: [0.0, 1.0, -1.0]
    output_data = np.array([[128, 138, 118, 148, 108]], dtype=np.uint8)
    interpreter.tensor.return_value = lambda: output_data
    
    scores = classify.get_scores(interpreter)
    self.assertEqual(len(scores), 5)
    self.assertAlmostEqual(scores[0], 0.0)
    self.assertAlmostEqual(scores[1], 1.0)
    self.assertAlmostEqual(scores[2], -1.0)
    self.assertAlmostEqual(scores[3], 2.0)
    self.assertAlmostEqual(scores[4], -2.0)

  def test_num_classes(self):
    interpreter = MagicMock()
    interpreter.get_output_details.return_value = [{'shape': [1, 1001]}]
    self.assertEqual(classify.num_classes(interpreter), 1001)

if __name__ == '__main__':
  unittest.main()
