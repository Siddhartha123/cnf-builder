### Example

```c++
int main() {
    signal x1, x2;
    x1.set_zero();
    x2.set_one();
    signal x3 = x1^x2;
    x3.print();

    return 0;
}
```

### Determination of co-factor


- let f_x be the return value, literal_of_interest = x.var * flag
- for each clause c in formula:
    - **if c is present in x.formula then ignore c
    - replace var with f_x.var
    - if c contains x.var, and flag==1 then ignore c
    - if c contains -x.var, and flag==-1 then ignore c
    - if c contains x.var, and flag==-1 then form a new clause with all literals of c except x.var
    - if c contains -x.var, and flag==1 then form a new clause with all literals of c except -x.var

- since some literals were deleted, it is possible that the resulting cnf may evaluate to
constant 1 or 0. hence we have to reduce the formula by substituting the trivial clauses (i.e. clauses of length 1)

- collect the list of single-literal clauses
- foreach of these literals, for each of the clauses in f_x:
    - either ignore the clause or remove the corresponding literal depending upon SAT
        - if the resulting clause is single, then insert into single-literal list
        - else if clause is empty, set zero = true

The last step in the algorithm is equivalent to finding cofactor of f_x w.r.t the trivial literals, hence the algorithm is recursive

** If the signal represented by variable of interest is a characteristic function of a sub-circuit, the formula of the signal should not be considered in f_x
