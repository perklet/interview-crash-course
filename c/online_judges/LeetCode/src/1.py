class Solution:
    # @return a tuple, (index1, index2)
     def twoSum(self, num, target):
         possible_answers = {}
         for i in range(len(num)):
             if num[i] in possible_answers:
                 return possible_answers[num[i]] + 1, i + 1
             else:
                 possible_answers[target - num[i]] = i
