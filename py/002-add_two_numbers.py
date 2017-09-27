#!/usr/bin/env python
# coding: utf-8

# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        head = ListNode(-1)
        cur = head
        remainder = 0
        while l1 or l2 or remainder:
            if l1:
                val1 = l1.val
                l1 = l1.next
            else:
                val1 = 0
            if l2:
                val2 = l2.val
                l2 = l2.next
            else:
                val2 = 0
            val = val1 + val2 + remainder
            if val >= 10:
                remainder = int(val / 10)
                val = val % 10
            else:
                remainder = 0
            cur.next = ListNode(val)
            cur = cur.next
        return head.next


