##### R Project 3: Binomial Distribution
##### Name: 
##### Version Number: 



### Part 1
## (C1): Store the size of your distribution

nBerTrial <- 8


## (C2) Store your probability of successes

pbty <-0.36


## (C3) Create a vector from 0 through the number of Bernoulli Trials of your distribution.

num_successes <- 0:nBerTrial



## (C4) Find Binomial Probabilities.

probabilities <- dbinom(num_successes,nBerTrial,pbty)


## (C5) Make num_successes into a factor.

successes <- factor(num_successes[1:(nBerTrial+1)])  


## (C6) Create a barplot.

barplot(probabilities, main = "Binomial Probabilities", xlab = "Successes",ylab = "Binomial Probabilities (PMF)", xlim = c(0,20), ylim = c(0,0.31), names.arg = successes)






### Part 2
## (C7) Random Sampling
set.seed(54)
sample_values <- rbinom(45, nBerTrial, pbty)




### Questions
## (Q1) Expected Value of Distribution?
	# Code:
  e <- nBerTrial * pbty
  
	# Result from Code:
  # Ans -> 2.88


## (Q2) Standard Deviation of Distribution?
	# Code:
  s <- sqrt(nBerTrial * pbty * (1-pbty))

	# Result from Code:
  # Ans -> 1.357645


## (Q3) Mean of random sample?
	# Code:
  x <- mean(sample_values)

	# Result from Code:
  # Ans -> 2.755556


## (Q4) Standard Deviation of random sample?
	# Code:
  y <- sd(sample_values)

	# Result from Code:
  # Ans -> 1.464047

## (Q5) Why do you think the mean and standard deviation from the sample is not exactly the same as the expected value and standard deviation from the distribution?
	# Answer:
  # The difference between expected value and standard deviation that I got form my random sample is quit  significant.The difference between those two value is 0.124
  # The difference between standard deviation of distribution and standard deviation of random sample is quit significant.The difference between those two value is 0.1064022
  # The reason why they both are not exactly same is due to random sampling and the increased number of trial. Since in our random sample the number of trial is increasing and the randomness is also incereasing that's the reason for those value not being same,


## (Q6) Would the success / failure condition be met in this case if we wanted to approximate using the Normal Distribution? Why or why not?
	# Code: 
  e1 <- nBerTrial * pbty
  f <- (nBerTrial * (1-pbty))

	# Solution:
  # Expected value for success: 2.88
  # Expected value for failure: 5.12
  # since expected value of success is not greater than 5 we can not approximate using the Normal Distribution.
  # In order to approximate using the Normal Distribution we need both expected value of success and failure to be greater than 5. 

