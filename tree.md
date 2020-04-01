# 树的遍历

树的递归遍历都非常简单，但是非递归遍历有时候不是很简单。一般做题的时候直接写递归版就行了，
但是对于三个基础的遍历方法，有时候会要求写迭代版本，基本就是花式用栈就行了。

## 前序遍历

### 递归版

```Python
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        return [root.val, *self.preorderTraversal(root.left), *self.preorderTraversal(root.right)]
```

### 非递归版

使用栈做了一个顺序的反转。

```Python
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        ans = []
        stack = []
        stack.append(root)
        while stack:
            node = stack.pop()
            ans.append(node.val)
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
        return ans
```

## 中序遍历

### 递归版

```Python
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        return [*self.inorderTraversal(root.left), root.val, *self.inorderTraversal(root.right)]
```

### 非递归版

```Python
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        ans = []
        stack = []
        node = root
        while stack or node:
            while node:
                stack.append(node)
                node = node.left
            left = stack.pop()
            ans.append(left.val)
            if left.right:
                node = left.right
        return ans
```

## 后续遍历

[LeetCode 145](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)

### 递归版

```Python
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        return [*self.postorderTraversal(root.left), *self.postorderTraversal(root.right), root.val]
```

### 非递归版

这个方法还是有点 trick 的，类似于前序遍历，但是把左右子树反过来了，最后再翻转一遍，就变成
了后序遍历。

```
    1
   / \
  2   3
```

比如：前序遍历是 123, 现在这种遍历方式是 132, 在翻转一次正好是 231, 也就是后续遍历了。

```Python
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        ans = []
        stack = [root]
        while stack:
            node = stack.pop()
            ans.append(node.val)
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)
        return list(reversed(ans))
```

## 参考资料

1. https://leetcode-cn.com/problems/binary-tree-preorder-traversal/solution/leetcodesuan-fa-xiu-lian-dong-hua-yan-shi-xbian-2/
