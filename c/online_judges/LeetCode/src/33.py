class Solution:
    # @param {integer[]} nums
    # @param {integer} target
    # @return {integer}
    def search(self, nums, target):
        i = 0
        for n in nums:
            if target == n:
                return i
            i += 1
        return -1
            
