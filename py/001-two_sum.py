#!/usr/bin/env python
# coding: utf-8


class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        match_set = {}  # num => idx set
        for idx, n in enumerate(nums):
            if target - n not in match_set:
                match_set[n] = idx
            else:
                return match_set[target - n], idx

