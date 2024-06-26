##### R Final Project
##### Name: Tanuj Dave
##### Version Number: 1




## Task 1: Load the Dataset into R (Code)
school <- read.csv(file = "CPS_Dataset.csv")

gp2009 <- school$X10_Grade_Plan_2009
gp2010 <- school$X10_Grade_Plan_2010
spa <- school$Students_Passing_Algebra
gr <- school$Graduation_Rate



## Task 2: Summary Statistics for Students Passing Algebra
	# Summary Stats Code and Results
summary(spa)
#   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.    NA's 
#   3.80   33.70   54.15   53.83   73.47  100.00     436 
	
	# Variance Code and Results
var(spa,na.rm = TRUE)
#632.7849

	
	
	# Standard Deviation Code and Results
sd(spa,na.rm = TRUE)
#25.15522

	
	# Number of values that are not missing Code and Results
nNA <- 566-436
#130
	
	
## Task 3: Summary Statistics for Graduation Rate
	# Summary Stats Code and Results
summary(gr)
# Min. 1st Qu.  Median    Mean 3rd Qu.    Max.    NA's 
# 16.30   51.45   62.25   62.54   74.53   97.60     488 
	
	
	# Variance Code and Results
var(gr,na.rm = TRUE)
# 296.0686
	
	
	# Standard Deviation Code and Results
sd(gr,na.rm = TRUE)
#17.2066

	
	# Number of values that are not missing Code and Results
nna <- 566-488
#78

	
	
	
	
	
## Task 4: Histogram for Students Passing Algebra
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
hist(spa,right = FALSE,
     ylim = c(0,25),
     breaks = seq(0,120,10))




	# Describe histogram: symmetry?
# The histogram is not symmetric and has 3 peaks


	
	# Describe histogram: unimodal or bimodal or multimodal?
# the histogram is multimodal with 3 peaks/humps

	
	
## Task 5: Histogram for Graduation Rate
	## Remember to save your plot and also submit it to Gradescope.


	# Code:
hist(gr,
     right = FALSE,
     ylim = c(0,20),
     breaks = seq(0,100,10))



	# Describe histogram: symmetry?
  # The histogram has a relatively symmetric plot.


	
	# Describe histogram: unimodal or bimodal or multimodal?
	# the histogram is unimodal.



## Task 6: Boxplot for Students Passing Algebra
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
ba <- boxplot(spa,horizontal = TRUE)

	

	# Are there outliers present? No, there are no outliers
oalg <- ba$out
oalg


## Task 7: Boxplot for Graduation Rate
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
brate <- boxplot(gr,horizontal = TRUE)

	

	# Are there outliers present? No, there are no outliers
		or <- brate$out


		
## Task 8: Shapiro-Wilk Test for Students Passing Algebra
	# Code:
		shapiro.test(spa)


	# Copy and paste results here
		#		Shapiro-Wilk normality test
		#		
		#		data:  students_passing_algebra
		#		W = 0.97738, p-value = 0.02852


	# Do you think that your population is normally distributed?
		# No



	# Reason: 
		# the p value is too little than 0.05

		
		
	# Does your decision here match what you are seeing with your histogram from Task 4? Why or why not?
# Yes, the histogram did not have a normal distribution either.
		
		
		
		
		
		
## Task 9: Shapiro-Wilk Test for Graduation Rate
	# Code:
		shapiro.test(graduation_rate)



	# Copy and paste results here
		#Shapiro-Wilk normality test
		
		#data:  graduation_rate
		#W = 0.9884, p-value = 0.7067


	# Do you think that your population is normally distributed?
  # Yes,


	# Reason: It has a high pvalue greater than 0.05

		
		
	# Does your decision here match what you are seeing with your histogram from Task 5? Why or why not?
# The histogram was approximately normal and the test verifies the result.
		
		
		
		
		
		
## Task 10: Compare average PLAN scores from students tested Fall 2009 to the average PLAN scores from students tested Fall 2010.  Create a confidence interval, assuming equal variances. (See PDF for CI to create.)

	# Code:
		t.test(gp2009, gp2009, alternative = "two.sided",conf.level = 0.914 ,var.equal = TRUE)



	# Copy and paste results here
		#  Two Sample t-test
		
		#  data:  grade_plane_2009 and grade_plane_2010
		# t = 0.21531, df = 167, p-value = 0.8298
		#  alternative hypothesis: true difference in means is not equal to 0
		#  91.4 percent confidence interval:
		#    -0.5432962  0.6980481
		#  sample estimates:
		#    mean of x mean of y 
		#  15.14634  15.06897



	# State the parameter the confidence interval is for.
		# THe test is for the difference of means.

		
	# Write down the confidence interval.
		#-0.5432962 to  0.6980481
		



	# Write an interpretation of your confidence interval.
# We are 91.4 percent confident that the value is between  -0.5432962 and 0.6980481


	# We are interested in whether there is evidence that there is specific value difference between the PLAN scores for the two years. (See PDF for more specifics.)
		# Is there evidence this is true?
	  # No


		# Reason why or why not.
  # 0 lies in the CI, thus there is no evidence of difference of the means.
		
		
		
		
		
		
		
## Task 11: Create a confidence interval for the variance of Graduation Rate. (See PDF for CI to create.) Ignore any warnings generated.

	# Code:
		library(EnvStats)
		varTest(gr,
		        alternative = "two.sided",
		        conf.level = 0.942)


	
	# Copy and paste results here
		#Chi-Squared Test on Variance
		
		#data:  graduation_rate
		#Chi-Squared = 22797, df = 77, p-value < 2.2e-16
		#alternative hypothesis: true variance is not equal to 1
		#94.2 percent confidence interval:
		#223.0797 412.5564
		#sample estimates:
		#variance 
		#296.0686 

	
	# State the parameter the confidence interval is for.
		#variance


	
	# Write down the confidence interval.
		# 223.0797 to 412.5564



	# Write an interpretation of your confidence interval.
		# We are 94.2 percent sure that the value lies between 223.0797 and 412.5564



	# What assumption did we need to make to construct this confidence interval?
		#Assume that the population is approximately normal
  


	# Do you think that this assumption was met? You should reference an earlier Task from this project to answer this question.
  #Yes, the histogram for the graduation rate was approximately normal

	
	

	
## Task 12: Hypothesis Test for Students Passing Algebra
	# What conditions must you satisfy to perform this test? Do you think they are met?  Why or why not?
	# The population must be approximately normal and variance must be unknown for population.



	# State the hypotheses:
		#H0: mu = 50
		#H1: mu < 50
	
	
	
	
	# Code
		t.test(spa, mu = 50,
		       alternative = "less",
		       conf.level = 1-0.024)
	
	
	# Copy and paste results here
		
	#data:  students_passing_algebra
	#t = 1.7356, df = 129, p-value = 0.9575
	#alternative hypothesis: true mean is less than 50
	#97.6 percent confidence interval:
	# -Inf 58.23372
	#sample estimates:
	# mean of x 
	#53.82923 
	
	
	
	# State the Test Statistic Value: 1.7356
	

	# State the P-Value: 0.9575

	
	# Decision from P-Value (see PDF for significance level): Failed to reject Null hypothesis

	
	# Conclusion from P-Value: Not enough evidence


	
	# State the critical value. Provide your code and results.
		qt(0.024, 129, lower.tail = TRUE)
		#-1.996361

			
	# State the critical region.
		#Reject Null Hypothesis if t < -1.996
		#Since t = 1.7356 > -1.9963.
		# We Do not reject the hypothesis.


	# Would you make the same decision based on the critical region that you did with your p-value? Why or why not?
		# Yes, values outside the rejection region will have p value higher than out significance level





