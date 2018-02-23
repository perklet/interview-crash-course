#!/usr/bin/env python
# coding: utf-8

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        longest = 0
        length = 0
        char_set = {}  # this could be a list of 26 length, but, hey, we are using python.
        start = 0
        for idx, c in enumerate(s):
            start = max(start, char_set.get(c, -1) + 1)  # 考虑新加入字符之后, 对子串的影响
            char_set[c] = idx
            length = idx - start + 1
            longest = max(longest, length)
        return longest
