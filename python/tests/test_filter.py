#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see http:#www.gnu.org/licenses/.
#

import unittest

import numpy as np

from smile.filter import Filter


class TestFilter(unittest.TestCase):
    data = np.array([[1, 20, 300, 4000],
                 [2, 30, 400, 5000],
                 [3, 40, 500, 6000],
                 [4, 50, 600, 7000],
                 [5, 60, 700, 8000],
                 [6, 70, 800, 9000],
                 [7, 80, 900, 0],
                 [8, 90, 0, 1000],
                 [9, 0, 100, 2000]])

    def test_execute_equal_condition(self):
        data_filter = Filter()
        data_filter.equal(0, 3)
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[3, 40, 500, 6000]])

    def test_execute_less_equal_condition(self):
        data_filter = Filter()
        data_filter.less_equal(1, 40)
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[1, 20, 300, 4000],
                                                                       [2, 30, 400, 5000],
                                                                       [3, 40, 500, 6000],
                                                                       [9, 0, 100, 2000]])

    def test_execute_less_condition(self):
        data_filter = Filter()
        data_filter.less(2, 200)
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[8, 90, 0, 1000],
                                                                       [9, 0, 100, 2000]])

    def test_execute_greater_condition(self):
        data_filter = Filter()
        data_filter.greater(2, 700)
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[6, 70, 800, 9000],
                                                                       [7, 80, 900, 0]])

    def test_execute_greater_equal_condition(self):
        data_filter = Filter()
        data_filter.greater_equal(2, 700)
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[5, 60, 700, 8000],
                                                                       [6, 70, 800, 9000],
                                                                       [7, 80, 900, 0]])

    def test_execute_in_condition(self):
        data_filter = Filter()
        data_filter.is_in(2, (300, 100, 600))
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[1, 20, 300, 4000],
                                                                       [4, 50, 600, 7000],
                                                                       [9, 0, 100, 2000]])

    def test_execute_complex_cases(self):
        data_filter = Filter()
        data_filter.greater_equal(0, 3)
        data_filter.less(1, 90)
        data_filter.is_in(2, (0, 700, 900))
        np.testing.assert_equal(data_filter.execute(TestFilter.data), [[5, 60, 700, 8000],
                                                                       [7, 80, 900, 0]])

        data_filter = Filter()
        data_filter.greater_equal(0, 7)
        data_filter.less(1, 50)
        data_filter.is_in(2, (0, 700, 900))
        self.assertEqual(data_filter.execute(TestFilter.data).shape, (0, 4))


if __name__ == '__main__':
    unittest.main()
