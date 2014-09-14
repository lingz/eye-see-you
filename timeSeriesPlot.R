#!/usr/bin/env Rscript

f <- file("stdin")
open(f)

x11()

dataframe <- data.frame()

count <- 1

while(length(line <- readLines(f,n=1)) > 0) {
  lineSplit <- strsplit(line, " ")[[1]]

  dataframe <- rbind(dataframe, as.numeric(lineSplit))
  if(count == 1) {
	names(dataframe) <- c("x1", "y1", "x2", "y2")
  }

  if(count %% 100 == 1){
 	plot(1, dataframe[count, 1]+1, col = "red", ylim = c(-2, 2), xlim = c(0, 201), ylab = "X", xlab = "Frame", type = "p", pch = 18)
 	abline(h=0)
 	abline(v=100.5)
  	lines(1+101, dataframe[count, 2]+1, col = "green", type = "p", pch = 18)

	lines(1, dataframe[count, 3]-1, col = "red", type = "p", pch = 18)
	lines(1+101, dataframe[count, 4]-1, col = "green", type = "p", pch = 18)
  } else {
  	lines(count%%100, dataframe[count, 1]+1, col = "red", type = "p", pch = 18)
  	lines(count%%100+101, dataframe[count, 2]+1, col = "green", type = "p", pch = 18)

	lines(count%%100, dataframe[count, 3]-1, col = "red", type = "p", pch = 18)
	lines(count%%100+101, dataframe[count, 4]-1, col = "green", type = "p", pch = 18)
  }

  count <- count+1

}

Sys.sleep(5)