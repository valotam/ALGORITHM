# Greedy Algorithm

| $I$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| $S(I)$ | 0 | MAX | MAX | MAX | MAX | MAX | MAX | MAX | MAX | MAX | MAX |

$$
\begin{matrix}
\text{if } & S(k) + P < S(k+W) \\
\text{then } & S(k+W) = S(k) + P (0 \le k \le F-E-W)
\end{matrix}
$$
