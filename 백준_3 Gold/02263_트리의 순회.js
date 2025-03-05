const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const n = inp[0][0];
const tree = Array.from({ length: n + 1 }, () => [0, 0]);

const inOrder = inp[1];
const postOrder = inp[2];

const idxOfInOrder = Array.from({ length: n + 1 }, () => -1);
for (let i = 0; i < n; i++) idxOfInOrder[inOrder[i]] = i;

function getRoot(inSt, inEd, poSt, poEd) {
  const root = postOrder[poEd];

  if (inOrder[inSt] != root)
    tree[root][0] = getRoot(
      inSt,
      idxOfInOrder[root] - 1,
      poSt,
      poSt + idxOfInOrder[root] - inSt - 1
    );
  if (inOrder[inEd] != root)
    tree[root][1] = getRoot(
      idxOfInOrder[root] + 1,
      inEd,
      poSt + idxOfInOrder[root] - inSt,
      poEd - 1
    );

  return root;
}

const ans = [];
function preOrder(root) {
  if (root == 0) return;

  ans.push(root);
  preOrder(tree[root][0]);
  preOrder(tree[root][1]);
}

preOrder(getRoot(0, n - 1, 0, n - 1));

console.log(ans.join(" "));
