g++ -std=c++11 -o src/ID3WithoutAndWithPruning src/ID3WithoutAndWithPruning.cpp
g++ -std=c++11 -o src/ID3AndC45RandomForest src/ID3AndC45RandomForest.cpp
g++ -std=c++11 -o src/calResult src/calResult.cpp
g++ -std=c++11 -o src/prepareBeforePredict src/prepareBeforePredict.cpp

if [ ! -d "result" ]; then
  mkdir result
fi

if [ -f "$src/main" ]; then
  rm src/main
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
	src/ID3WithoutAndWithPruning data/dataSet${i##*et} data/testData${i##*et} file${i##*et}
	src/calResult data/predictResultOfID3WithPruningfile${i##*et} data/rightResultfile${i##*et} result/resultOfID3WithPruning
	src/calResult data/predictResultOfID3WithoutPruningfile${i##*et} data/rightResultfile${i##*et}  result/resultOfID3WithoutPruning

  src/ID3AndC45RandomForest data/dataSet${i##*et} data/testData${i##*et} file${i##*et}
  src/calResult data/predictResultOfID3file${i##*et} data/rightResultfile${i##*et} result/resultOfID3RandomForest
  src/calResult data/predictResultOfC45file${i##*et} data/rightResultfile${i##*et}  result/resultOfC45RandomForest
done

gnuplot result_histogram.plt

rm data/testData* data/dataSet* src/ID3WithoutAndWithPruning src/ID3AndC45RandomForest src/calResult src/prepareBeforePredict \
  data/rightResultfile* data/predictResultOfID3WithPruningfile* data/predictResultOfID3WithoutPruningfile* \
  data/predictResultOfC45file*  data/predictResultOfID3file*


