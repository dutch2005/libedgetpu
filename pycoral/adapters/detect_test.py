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
"""Tests for pycoral.adapters.detect."""

import unittest
from unittest.mock import MagicMock, patch
import numpy as np
from pycoral.adapters import detect

class TestDetect(unittest.TestCase):

  def test_bbox_properties(self):
    bbox = detect.BBox(xmin=10, ymin=20, xmax=50, ymax=60)
    self.assertEqual(bbox.width, 40)
    self.assertEqual(bbox.height, 40)
    self.assertEqual(bbox.area, 1600)
    self.assertTrue(bbox.valid)

  def test_bbox_invalid(self):
    bbox = detect.BBox(xmin=50, ymin=60, xmax=10, ymax=20)
    self.assertFalse(bbox.valid)
    self.assertEqual(detect.BBox.iou(bbox, bbox), 0.0)

  def test_bbox_iou(self):
    a = detect.BBox(xmin=0, ymin=0, xmax=10, ymax=10)
    b = detect.BBox(xmin=5, ymin=5, xmax=15, ymax=15)
    # Intersection: (5,5,10,10) -> area 25
    # Union: 100 + 100 - 25 = 175
    # IoU: 25/175 = 1/7
    self.assertAlmostEqual(detect.BBox.iou(a, b), 1.0/7.0)

  @patch('pycoral.adapters.common.output_tensor')
  @patch('pycoral.adapters.common.input_size')
  def test_get_objects(self, mock_input_size, mock_output_tensor):
    mock_interpreter = MagicMock()
    mock_interpreter._get_full_signature_list.return_value = {}
    mock_input_size.return_value = (100, 100)
    
    # Mock output tensors for SSD-like model (boxes, classes, scores, count)
    # Common format: output_tensor(3).size == 1
    def side_effect(interpreter, i):
      if i == 0: return np.array([[[0.1, 0.1, 0.5, 0.5]]]) # boxes (ymin, xmin, ymax, xmax)
      if i == 1: return np.array([[1]]) # classes
      if i == 2: return np.array([[0.9]]) # scores
      if i == 3: return np.array([1]) # count
      return None

    mock_output_tensor.side_effect = side_effect
    
    objs = detect.get_objects(mock_interpreter, score_threshold=0.5)
    self.assertEqual(len(objs), 1)
    self.assertEqual(objs[0].id, 1)
    self.assertAlmostEqual(objs[0].score, 0.9)
    # Scaled to 100x100: (0.1, 0.1, 0.5, 0.5) -> (10, 10, 50, 50)
    self.assertEqual(objs[0].bbox.xmin, 10)
    self.assertEqual(objs[0].bbox.ymin, 10)
    self.assertEqual(objs[0].bbox.xmax, 50)
    self.assertEqual(objs[0].bbox.ymax, 50)

if __name__ == '__main__':
  unittest.main()
