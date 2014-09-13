#!/usr/bin/env Rscript

f <- file("stdin")
open(f)

x11()

dataframe <- data.frame()

count <- 1

while(length(line <- readLines(f,n=1)) > 0) {
  lineSplit <- strsplit(line, " ")[[1]]
  dataframe <- rbind(dataframe, as.numeric(lineSplit))
}

names(dataframe) <- c("x1", "y1", "x2", "y2")

par(mfrow = c(2, 1))

plot(1:dim(dataframe)[1], dataframe[, 1], col = "red", ylim = c(-1, 1), type = "l", ylab = "X", xlab = "Frame")
lines(1:dim(dataframe)[1], dataframe[, 3], col = "green")

plot(1:dim(dataframe)[1], dataframe[, 2], col = "red", ylim = c(-1, 1), type = "l", ylab = "Y", xlab = "Frame")
lines(1:dim(dataframe)[1], dataframe[, 4], col = "green")

Sys.sleep(5)