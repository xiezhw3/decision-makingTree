g++ -std=c++11 -o src/decisongMakingTreeMaker src/decisongMakingTreeMaker.cpp
g++ -std=c++11 -o src/calResult src/calResult.cpp
g++ -std=c++11 -o src/prepareBeforePredict src/prepareBeforePredict.cpp

if [ ! -d "result" ]; then
  mkdir result
fi

if [ -f "$src/decisongMakingTreeMaker" ]; then
  rm src/decisongMakingTreeMaker
fi

if [ -f "$src/calResult" ]; then
  rm src/calResult
fi

if [ -f "$src/prepareBeforePredict" ]; then
  rm src/prepareBeforePredict
fi

if [ -f "$data/testData*" ]; then
  rm data/testData*
fi

if [ -f "$data/dataSet*" ]; then
  rm data/dataSet*
fi

if [ -f "result/resultOfID3" ]; then
  rm result/resultOfID3*
fi

if [ -f "result/resultOfC45" ]; then
  rm result/resultOfC45*
fi

./src/prepareBeforePredict data/dataset.txt 100

for i in $(ls data/dataSet*); do
	src/decisongMakingTreeMaker data/dataSet${i##*et} data/testData${i##*et} file${i##*et}
	src/calResult data/predictResultOfC45file${i##*et} data/rightResultfile${i##*et} result/resultOfC45
	src/calResult data/predictResultOfID3file${i##*et} data/rightResultfile${i##*et}  result/resultOfID3
done

rm data/testData* data/dataSet* src/decisongMakingTreeMaker src/calResult src/prepareBeforePredict \
  data/rightResultfile* data/predictResultOfID3file* data/predictResultOfC45file*

gnuplot result_histogram.plt
