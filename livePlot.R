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
  	plot(dataframe[count, 1]-1, dataframe[count, 2], type = "p", col = "red", xlim = c(-2, 2), ylim = c(-1, 1), xlab = "X", ylab = "Y")
  } else {
  	lines(dataframe[count, 1]-1, dataframe[count, 2], col = "red", type = "p")
  }

  lines(dataframe[count, 3]+1, dataframe[count, 4], col = "green", type = "p")
  count <- count + 1
}

Sys.sleep(5)