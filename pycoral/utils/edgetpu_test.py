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
"""Tests for pycoral.utils.edgetpu."""

import unittest
from unittest.mock import MagicMock, patch
import sys
import numpy as np
import ctypes

# Mock the C++ extension module and missing dependencies so tests can run
mock_pywrap = MagicMock()
sys.modules['pycoral.pybind'] = MagicMock()
sys.modules['pycoral.pybind._pywrap_coral'] = mock_pywrap

mock_tflite = MagicMock()
sys.modules['tflite_runtime'] = MagicMock()
sys.modules['tflite_runtime.interpreter'] = mock_tflite

from pycoral.utils import edgetpu


class TestEdgeTpu(unittest.TestCase):

  @patch('pycoral.utils.edgetpu.tflite.load_delegate')
  def test_load_edgetpu_delegate(self, mock_load_delegate):
    mock_load_delegate.return_value = 'delegate_obj'
    delegate = edgetpu.load_edgetpu_delegate({'device': 'pci:0'})
    self.assertEqual(delegate, 'delegate_obj')
    mock_load_delegate.assert_called_once()

  @patch('pycoral.utils.edgetpu.invoke_with_membuffer')
  def test_run_inference_numpy(self, mock_invoke):
    mock_interpreter = MagicMock()
    mock_interpreter.get_input_details.return_value = [{'shape': [1, 10], 'index': 0}]
    mock_interpreter._native_handle.return_value = 12345
    
    data = np.zeros(10, dtype=np.uint8)
    edgetpu.run_inference(mock_interpreter, data)
    
    mock_invoke.assert_called_once_with(12345, data.ctypes.data, 10)

  @patch('pycoral.utils.edgetpu.invoke_with_bytes')
  def test_run_inference_bytes(self, mock_invoke):
    mock_interpreter = MagicMock()
    mock_interpreter.get_input_details.return_value = [{'shape': [1, 5]}]
    mock_interpreter._native_handle.return_value = 12345
    
    data = b'\x00' * 5
    edgetpu.run_inference(mock_interpreter, data)
    
    mock_invoke.assert_called_once_with(12345, data)

  def test_run_inference_invalid_size(self):
    mock_interpreter = MagicMock()
    mock_interpreter.get_input_details.return_value = [{'shape': [1, 10]}]
    
    data = np.zeros(5, dtype=np.uint8)
    with self.assertRaises(ValueError):
      edgetpu.run_inference(mock_interpreter, data)

  def test_is_valid_ctypes_input(self):
    # Valid
    ptr = ctypes.c_void_p(0)
    self.assertTrue(edgetpu._is_valid_ctypes_input((ptr, 100)))
    
    # Invalid types
    self.assertFalse(edgetpu._is_valid_ctypes_input(None))
    self.assertFalse(edgetpu._is_valid_ctypes_input((None, 100)))
    self.assertFalse(edgetpu._is_valid_ctypes_input((ptr, "100")))

if __name__ == '__main__':
  unittest.main()
