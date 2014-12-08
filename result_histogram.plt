set boxwidth 0.4 absolute
set term jpeg
set xrange[-1:100]
set yrange[0:1]
set ylabel "accuracy of predict"
set output "result/resultOfC45.jpeg"
plot "result/resultOfC45" with boxes
replot
set output "result/resultOfID3.jpeg"
plot "result/resultOfID3" with boxes
quit