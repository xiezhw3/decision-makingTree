set boxwidth 0.4 absolute
set term jpeg
set xrange[-1:100]
set yrange[0:1]
set ylabel "accuracy of predict"
set output "result/resultOfID3WithPruning.jpeg"
plot "result/resultOfID3WithPruning" with boxes
replot
set output "result/resultOfID3WithoutPruning.jpeg"
plot "result/resultOfID3WithoutPruning" with boxes
replot
set output "result/resultOfC45RandomForest.jpeg"
plot "result/resultOfC45RandomForest" with boxes
replot
set output "result/resultOfID3RandomForest.jpeg"
plot "result/resultOfID3RandomForest" with boxes
quit