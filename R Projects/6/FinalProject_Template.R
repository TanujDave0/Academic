##### R Final Project
##### Name: Dhruv Patel 
##### Version Number: 1




## Task 1: Load the Dataset into R (Code)
  school <- read.csv(file = "CPS_Dataset.csv")
  students_passing_algebra <- school$Students_Passing_Algebra
  graduation_rate <- school$Graduation_Rate
  grade_plane_2009 <- school$X10_Grade_Plan_2009
  grade_plane_2010 <- school$X10_Grade_Plan_2010
    




## Task 2: Summary Statistics for Students Passing Algebra
	# Summary Stats Code and Results
  summary(students_passing_algebra)
	#Min. 1st Qu.  Median    Mean 3rd Qu.    Max.    NA's 
  #3.80   33.70   54.15   53.83   73.47  100.00     436 
  
	
	# Variance Code and Results
  var(students_passing_algebra,na.rm = TRUE)
	#632.7849
	
	# Standard Deviation Code and Results
  sd(students_passing_algebra,na.rm = TRUE)
  #25.15522
	
	# Number of values that are not missing Code and Results
  not_NA <- 566-436
	#130


	
	
## Task 3: Summary Statistics for Graduation Rate
	# Summary Stats Code and Results
  summary(graduation_rate)
  #   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.    NA's 
  # 16.30   51.45   62.25   62.54   74.53   97.60     488 
	
	
	# Variance Code and Results
  var(graduation_rate,na.rm = TRUE)
	#296.0686
	
	# Standard Deviation Code and Results
  sd(graduation_rate,na.rm = TRUE)
  #17.20664
	
	# Number of values that are not missing Code and Results
  not_na <- 566-488
	#78
	
	
## Task 4: Histogram for Students Passing Algebra
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
  hist(students_passing_algebra,right = FALSE, ylim = c(0,25) ,breaks = seq(0,120,10))
  
  

	# Describe histogram: symmetry?
  #No, histogram for Students Passing Algebra is not symmetric.   


	
	# Describe histogram: unimodal or bimodal or multimodal?



	
	
	
	
## Task 5: Histogram for Graduation Rate
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
  
  hist( graduation_rate, right = FALSE, ylim = c(0,20), breaks = seq(0,100,10))



	# Describe histogram: symmetry?
  #The histogram is relatively symmetric. 


	
	# Describe histogram: unimodal or bimodal or multimodal?
		
		
		
		
		



## Task 6: Boxplot for Students Passing Algebra
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
  box_alg <- boxplot(students_passing_algebra,horizontal = TRUE)
	

	# Are there outliers present?
  outlier_alg <- box_alg$out
		
	#No there is no outlier are present 	
		
		


## Task 7: Boxplot for Graduation Rate
	## Remember to save your plot and also submit it to Gradescope.

	# Code:
  box_rate <- boxplot(graduation_rate,horizontal = TRUE)
	

	# Are there outliers present?
		
	oulier_rate <- box_rate$out	
	#No there is no outlier are present 	
		


		
## Task 8: Shapiro-Wilk Test for Students Passing Algebra
	# Code:
	shapiro.test(students_passing_algebra)


	# Copy and paste results here
	#Shapiro-Wilk normality test
	
	#data:  students_passing_algebra
	#W = 0.97738, p-value = 0.02852
	


	# Do you think that your population is normally distributed?



	# Reason: 

		
		
	# Does your decision here match what you are seeing with your histogram from Task 4? Why or why not?
  #Yes, 
		
		
		
		
		
		
## Task 9: Shapiro-Wilk Test for Graduation Rate
	# Code:
  shapiro.test(graduation_rate)
  

	# Copy and paste results here
  #Shapiro-Wilk normality test
  
  #data:  graduation_rate
  #W = 0.9884, p-value = 0.7067


	# Do you think that your population is normally distributed?
  


	# Reason: 

		
		
	# Does your decision here match what you are seeing with your histogram from Task 5? Why or why not?

		
		
		
		
		
		
## Task 10: Compare average PLAN scores from students tested Fall 2009 to the average PLAN scores from students tested Fall 2010.  Create a confidence interval, assuming equal variances. (See PDF for CI to create.)

	# Code:

  t.test(grade_plane_2009,grade_plane_2010, alternative = "two.sided",conf.level = 0.914 ,var.equal = TRUE)

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
  


		
	# Write down the confidence interval.
  #CI = (-0.5432962, 0.6980481)


	# Write an interpretation of your confidence interval.



	# We are interested in whether there is evidence that there is specific value difference between the PLAN scores for the two years. (See PDF for more specifics.)
		# Is there evidence this is true?


		# Reason why or why not.

		
		
		
		
		
		
		
## Task 11: Create a confidence interval for the variance of Graduation Rate. (See PDF for CI to create.) Ignore any warnings generated.

	# Code:
  library(EnvStats)
  varTest(graduation_rate,alternative = "two.sided",conf.level = 0.942)

	
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


	
	# Write down the confidence interval.



	# Write an interpretation of your confidence interval.



	# What assumption did we need to make to construct this confidence interval?



	# Do you think that this assumption was met? You should reference an earlier Task from this project to answer this question.
  # 9.12 or 8.5 
	
	
	
	
	

	
## Task 12: Hypothesis Test for Students Passing Algebra
	# What conditions must you satisfy to perform this test? Do you think they are met?  Why or why not?
  


	# State the hypotheses:
		#H0: mu = 50 
		#H1: mu < 50
	
	
	
	# Code
  t.test(students_passing_algebra, mu = 50 , alternative = "less", conf.level = 1-0.024)
	
	
	# Copy and paste results here

  #One Sample t-test
  
  #data:  students_passing_algebra
  #t = 1.7356, df = 129, p-value = 0.9575
  #alternative hypothesis: true mean is less than 50
  #97.6 percent confidence interval:
   # -Inf 58.23372
  #sample estimates:
   # mean of x 
  #53.82923 
	
	
	# State the Test Statistic Value:
  #t = 1.7356

	# State the P-Value:
  #p-value = 0.9575
	
	# Decision from P-Value (see PDF for significance level):
  #fail to reject NULL hypothesis 

	
	# Conclusion from P-Value:
  #There is not enough evidence 

	
	# State the critical value. Provide your code and results.
  qt(0.024,129,lower.tail = TRUE)
  #-1.996361
			
	# State the critical region.
  #Reject Null hypothesis if t < -1.996361. since t = 1.7356 is greater than -1.996361 therefore we fail to reject hypothesis. 


	# Would you make the same decision based on the critical region that you did with your p-value? Why or why not?
  # yes, any value outside the rejection region will have a p-value greater than our significance level. 





