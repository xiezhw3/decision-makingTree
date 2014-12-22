#决策树c++实现
##算法实现
>采用 ID3 和 C4.5 两种算法来实现决策树的生成，另外用使用的是李航的《统计学习方法》里面的决策树剪枝算法进行剪枝，第三个是使用随机森林算法对决策树进行优化

##文件结构
	.
	├── LICENSE
	├── README.MD
	├── data
	│   └── dataset.txt
	├── data description
	│   └── data description.txt
	├── result
	├── result_histogram.plt
	├── run.sh
	├── src
	│   ├── ID3AndC45RandomForest.cpp
	│   ├── ID3WithoutAndWithPruning.cpp
	│   ├── calResult.cpp
	│   ├── decisionMakingTree.h
	│   ├── entropy.h
	│   ├── fileProcesser.h
	│   ├── informationGain.h
	│   ├── node.h
	│   ├── predict.h
	│   ├── predictWithMultiTree.h
	│   ├── prepareBeforePredict.cpp
	│   ├── pruningOfTheTree.h
	│   └── table.h
	└── test
	    ├── tableTest.cpp
	    ├── testDecisionTreeMaker.cpp
	    ├── testEntropy.cpp
	    └── testInformationGain.cpp
        
 
##运行描述

> 运行脚本
>
	$bash run.sh


对测试的结果画了条形图，用到了 gunplot 工具，如果你没有安装这个工具，你可以去
[gunpot](http://www.gnuplot.vt.edu/) 这里下载一个进行安装。
 
 
###算法测试
 在上面的文件中，dataset.txt 是来自美国的选举数据，数据集的描述在文件 data description.txt 中。
 
 在我的测试里面，对训练数据集dataset.txt进行分割，在 dataset.txt 中随机选出100组数据作为预测数据，另外的335组数据作为训练数据集。
 
 一共进行了 100 组测试，测试方式是将100组测试数据的特征输入到决策树，将决策树的输出结果与正确的结果进行对比，计算正确率
 
 
###测试结果
测试结果可以在result文件夹下看到，其中

- resultOfC45RandomForest 是C45算法经过随机森林的结果
- resultOfID3RandomForest 是ID3算法经过随机森林的结果
- resultOfID3WithoutPruning 是ID3算法不进行剪枝的结果
- resultOfID3WithPruning 是ID3算法剪枝的结果

 
 
 	
 