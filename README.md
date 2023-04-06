# optimze-matrix-instance

## 📌 Background 

It is an example of the matrix optimization problem that I met in practice, and these solutions refer to how-to-optimize-gemm ([🔗 ref1](https://github.com/flame/how-to-optimize-gemm), [🔗 ref2](https://github.com/BBuf/how-to-optimize-gemm)).


The following is a description of the problem in the actual scenario:
- Due to the code is directly converted from Matlab using tools, there will be some very naive optimization points.
- The module to be optimized contains 30 continuous loops and all matrix elements are of the double type.
- After analyzing the hot spots, the tenth loop is chosen as an example, and the tenth loop is actually the multiplication of three matrices.
    - The matrix names are changed to meaningless names $a,b,c$ for the sake of privacy and specification. $mid_res$ means intermediate result of multiplication of the first two matrices $a \times b$, and $res$ means the final result of multiplication of the last two matrices $mid \_res \times c$
    - $a$ is a matrix with 60 rows and 120 cols; $b$ (120, 60); and c (60, 60); They are all stored in columns before optimization (include $mid \_ res$).
- The module's platform architecture is primarily ARM64, hence ARM64 has undergone further optimization.

## 🛸 Code Attention

> Only the tenth loop is selected individually in the code to illustrate the optimization concept.

## 🥥 Analysis

> The analytical part will be translated later because I'm currently preoccupied with job searching 🥲 . This is the Chinese translation of the analysis portion, and here is the [link](https://blog.neysaban.one/article/7367663c-3a3c-44dd-aae7-db9676c35d09) to my blog.

