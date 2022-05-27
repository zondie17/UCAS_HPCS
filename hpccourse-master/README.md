# 国科大高性能计算系统复习

    源代码是老师课上的展示，代码大部分由可神提供，cannon算法由鸣哥提供，往年试题来自pinjie老兄。我稍微补充沿着思路添加了一点点，目前改版本的代码基于openmpi 4.0.3，慢慢总结完善
---

- 代码风格:一个头文件站到底，一个main站到底。如果想要添加模块，在main里面添加`#define xxx`
- 有一些函数是4.0.3才有的,新比如`MPI_Type_get_extent`,`MPI_Get_address`等等，如果报错，参考[新老接口对比](https://www.open-mpi.org/faq/?category=mpi-removed)
- 其中exam1.c和exam2.c是往年考试题(当作是纸上写代码了，我不保证不报错)

