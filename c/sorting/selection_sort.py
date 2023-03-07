# coding: utf-8

'''
选择排序的好处是，数据移动是最少的。复杂度是O(n^2)
'''

def selection_sort(lst):
    for i in range(len(lst)):
        min_index = i
        for j in range(i, len(lst)):
            if lst[min_index] > lst[j]:
                min_index = j
        lst[i], lst[min_index] = lst[min_index], lst[i]
    return lst

if __name__ == '__main__':
    print(selection_sort([1, 2, 3]))
    print(selection_sort([]))
    print(selection_sort([2, 3, 1]))
    print(selection_sort([2, 3, 1, 4, 5, 7, 6]))
