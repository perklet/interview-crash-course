# coding: utf-8

'''
插入排序的好处是，当数组基本有序的时候，复杂度是近似线性的。复杂度是O(n^2)
'''

def sort(lst):
    for i in range(len(lst)):
        for j in range(i, 0, -1):
            if lst[j] > lst[j-1]:
                break
            lst[j], lst[j-1] = lst[j-1], lst[j]
    return lst

if __name__ == '__main__':
    print(sort([2, 2, 3]))
    print(sort([]))
    print(sort([2, 3, 1]))
    print(sort([2, 3, 1, 4, 5, 7, 6]))
