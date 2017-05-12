# MySTL
> A subset of SGI STL

## 空间适配器

二级空间分配策略：

+ 当size>128时，直接进行malloc分配内存空间，free释放空间
+ 当size<128时，由内存池memory pool进行空间的管理。
