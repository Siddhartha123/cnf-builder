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