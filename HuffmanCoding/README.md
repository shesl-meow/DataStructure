# README

## 运行说明

如果你有 `gnu` 环境，可以直接运行以下命令：

```bash
$ make
```

该命令会对源程序进行编译。然后执行以下命令：

```bash
$ ./main
```

该命令会执行编译后的 `c++` 程序。


你也可以把需要测试的构建哈夫曼树的句子写在 `./data/tree_build.txt` 这个文件中，需要测试的 01 写在 `./data/text_dor_decode.txt` 这个文件中。然后运行以下命令即可测试：

```bash
$ ./run.sh
```

*PostScript*: 

- 这是一个 bash 脚本；
- 他通过 `interact.py` 这个 `python` 文件，调用 `pwntools` 这个库与生成的 `main` 程序进行交互；
- 通过 `split.awk` 这个 `awk` 文件，将生成的文件划分成不同的文件；
- 结果全部在 `./data/` 这个文件夹当中。

## 文件说明

### Display

该文件定义了用于在终端显示的对象，全部定义在命名空间 `Display` 中。

- `DisplayMap` ：主要成员变量是一个二维 `std::string` 型数组，用于表示显示在终端的字符。

- `BinTreeMap`：派生自 `DisplayMap`，用于显示二叉树的一个对象。显示效果大致如下：

  ```bash
  .---2        
  2            
  |       .---1
  |   .---3    
  |   |   '---2
  '---4        
      |   .---1
      '---3    
          '---2
  ```

- `CodingMap`：派生自 `BinTreeMap`，用于在进行哈夫曼编码时的显示用于哈夫曼编码的哈夫曼树。显示效果如下：

  ```bash
              .---1: [blank]
          .---2    
          |   '---1: H
      .---4        
      |   '---2: o    
  .---7            
  |   '---3: l        
  11                
  |       .---1: W    
  |   .---2        
  |   |   '---1: d    
  '---4            
      |   .---1: e    
      '---2        
          '---1: r
  ```

### Tree

该文件定义了用于存储树状结构的对象，全部定义在命名空间 `Tree` 中。

- `BinTree` ：用于存储二叉树对象的类
- `HuffmanTree`：用于存储哈夫曼树对象的类，其派生自 `BinTree`。

### Coding

该文件旨在定义编码方式，主要实现的是哈夫曼编码，全部定义在命名空间 `Coding` 中。

- `AbsctractCoding`：用于实现编码方式的抽象基类。
- `HaffmanCoding`：用于实现哈夫曼编码的类，派生自 `AbstrctCoding`。
