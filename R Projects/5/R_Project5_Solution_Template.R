##### R Project 5: Central Limit Theorem
##### Name: Tanuj Dave
##### Version Number: 1



## (C1) Load the file Cars_Dataset.csv into R
cars <- read.csv("Cars_Dataset.csv")
mpg <- cars$Overall_MPG
category <- cars$Weight_Category



## (C2) Table of category
	# Code
table(category)


	# Copy and paste results here
#category
#Heavy Weight  Light Weight Medium Weight 
#20            24           168


	# What category has the most cars?
# medium weight has the most cars (168).

	# What category has the least cars?
# heavy weight has the least cars (20).



## (C3) Find estimates for the Mean, Variance, Standard Deviation Estimates for mpg using Built-In R Functions

	# Mean Code
mean(mpg)

	# Copy and paste mean results here
# 24.70047
	
	
	# Variance Code
var(mpg)
	
	# Copy and paste variance results here
# 37.07929

	# Standard Deviation Code
sd(mpg)
	
	# Copy and paste standard deviation results here
# 6.089277



## (C4) Histogram of mpg
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
hist(mpg, right = FALSE, breaks = seq(10, 60, 5))


	# Describe your histogram:
# The histogram is skewed right, and has an outlier.





# (C5) Shapiro-Wilk test on mpg

	# Code:
shapiro.test(mpg)

	# Copy and paste results here

#Shapiro-Wilk normality test

#data:  mpg
#W = 0.91039, p-value = 5.28e-10


	# Do you think that your population is normally distributed?
# no

	# Reason: 
# the p value is smaller than 0.05, thus it is not normally distributed
# Based on the histogram graph of the mpg, since it is skewed right,
#it is not normally distributed



	

# (C6) Copy and paste function, then run it.
sampling_jp <- function(dataset, seed_value, num_samples, sizejp){
  samples1 <- matrix(NA, nrow = num_samples, ncol = sizejp)
  set.seed(seed_value)
  for(i in 1:num_samples){
    samples1[i,] <- sample(dataset, size = sizejp, replace = TRUE)
  }
  rowmeans1 <- rowMeans(samples1)
  graph <- hist(rowmeans1, right = FALSE, xlab = "Sample Means",
                main = "Histogram",
                sub = paste("Size = ", sizejp))
  sw <- shapiro.test(rowmeans1)
  result <- list(SampleMeans = rowmeans1, Shapiro = sw, Histogram = graph)
  return(result)
}




# (Q7) Describe the difference between the terms "number of samples" and "sample size".

	# Number of Samples: is the total number of samples taken into account


	# Sample Size: is the total number of entries in each sample, or the size of the sample.




# (Q8) Describe what each individual part is doing in (C6) for code provided


	# sample() does: randomly returns a sample from the given distribution 
# the number of sample


	# dataset does: provides the data for sample to choose randomly from


	# size = sizejp does: defines the number of entries in the sample that is returned by sample() 


	# replace = TRUE does: enables re-choosing an entry from the dataset, thus duplicates are allowed.






# (C9) Build sampling distribution of samples of mpg
	## Remember to save your histogram and also submit it to Gradescope.

	# Code:
run1 <- sampling_jp(mpg, 20, 95, 8)


	
	# Copy and paste Shapiro-Wilk test results here

#Shapiro-Wilk normality test

#data:  rowmeans1
#W = 0.93428, p-value = 0.0001328




# (C10) Build sampling distribution of samples of mpg
	## Remember to save your histogram and also submit it to Gradescope.

	# Code:
run2<-sampling_jp(mpg, 20, 95, 207)


	
	# Copy and paste Shapiro-Wilk test results here
#$Shapiro

#Shapiro-Wilk normality test

#data:  rowmeans1
#W = 0.99255, p-value = 0.8789





# (Q11) From (C9): Does it appear normally distributed?  Why or why not?
	# Normally Distributed (Yes or No): No

	# Reason using histogram:
# The run1 histogram is skewed right with outliers thus, it is not normally
# distributed.


	# Reason using the Shapiro-Wilk Test:
#the p value produced by the test is p-value = 0.0001328, which is less than 0.05
# that we use to determine the normality. Thus, the distribution is not normal.





# (Q12) From (C10): Does it appear normally distributed?  Why or why not?
	# Normally Distributed (Yes or No): Yes

	# Reason using histogram:
# The graph is fairly normally distributed as it as a shape resembling a bell curve
# with peak in the middle, though it has 2 peaks, they are close enough.



	# Reason using the Shapiro-Wilk Test:
# The p value is p-value = 0.8789 which is greater than 0.05
# which we are using to determine normality, thus it has a normal distribution.




# (Q13) CLT?
	# Can CLT be used in (C9)?: No

	# Reason: Since the sample size 8 < 30, we need to check if the population is not too
# different from the normal, but checking the population histogram, it is not normal. Thus,
# we cannot use CLT for C9


	# Can CLT be used in (C10)?: Yes

	# Reason: The sample size 207 > 30, thus using CLT would be fine.




# (Q14) Expected Value of the Sample Mean using CLT formulas

	# Code for first sample size:
mean(mpg)


	# Copy and paste results here, 24.70047




	# Code for second sample size:
mean(mpg)


	# Copy and paste results here, 24.70047

	
	
	
	
# (Q15) Standard Deviation of the Sample Mean using CLT formulas

	# Code for first sample size: sd(mpg)/sqrt(8)



	# Copy and paste results here: 2.152884




	# Code for second sample size: sd(mpg)/sqrt(207)



	# Copy and paste results here: 0.423234
	
	
	
	
	
# (C16) Average of the Sample Means from C9 and C10

	# Code for average of sample means from C9: mean(run1$SampleMeans)


	# Copy and paste results here: 24.60658



	# Code for average of sample means from C10: mean(run2$SampleMeans)


	# Copy and paste results here: 24.72713

	
	
# (C17) Standard Deviation of the Sample Means from C9 and C10

	# Code for standard deviation of sample means from C9: sd(run1$SampleMeans)


	# Copy and paste results here: 2.243135



	# Code for standard deviation of sample means from C10: sd(run2$SampleMeans)


	# Copy and paste results here: 0.4183305
	
	
	



	
# (Q18) Does the CLT approximation appear to get better as the sample size increased? Why or why not?

	# Does it get better? Yes


	# Reason: As the  sample size increases, the standard deviation of the mean of the samples get closer to
# the actual mean as it more closely resembles the original data and has more and more chunks of data from the
# dataset thus mean/average gets closer and the deviation starts going toward the original one.




