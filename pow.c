#include<stdio.h>
#include<limits.h>
#include<math.h>

double intPower(long int x, long int n);
double floatPower(double x, double n);

int main()	//Driver function
{
	short int flag;
	int t;
	long int li_x,li_n;
	double d_x,d_n;
	double ans;

	printf("To use the power function when x,n are integers, press '0'\n");
	printf("To use the power function when x,n are floating point numbers, press '1'\n");
	scanf("%hi",&flag);
	printf("Enter the number of test cases : ");
	scanf("%d",&t);
	
	printf("Input given : x and n\n");
	printf("Anwser printed : x^n\n\n");
	
	if(!flag)
	{
		while(t--)
		{
			printf("Enter x and n :");
			scanf("%ld%ld",&li_x,&li_n);
			ans=intPower(li_x,li_n);
			if(ans != INT_MAX)
				printf("%lf\n",ans);
			else
				printf("ERROR\n");
		}
	}
	else
	{
		while(t--)
		{
			printf("Enter x and n :");
			scanf("%lf%lf",&d_x,&d_n);
			ans=floatPower(d_x,d_n);
			if(ans != INT_MAX)
				printf("%lf\n",ans);
			else
				printf("ERROR\n");
		}
	}
	
	return 0;
}

//	x^n = e^(n*log(x))

//Implementation
//	e^p = 1 + p + (p^2)/2! + (p^3)/3! + .....
//	where p=n*log(x)
double floatPower(double x, double n)
{
	float p;
	const double err=0.000000000001;
	double ans,e_p,term;
	int i,ans_sign_flag,complex;
	
	if(n==0)	//	(-inf < x < inf) & (n = 0)
	{
		ans=1;
	}
	else if(x == 0)
	{
		if(n>0)	//	(x = 0) & (0 < n < inf)
		{
			ans=0;
		}
		else	//	(x = 0) & (-inf < n < 0)
		{
			ans=INT_MAX;
		}
	}
	else	//	(x != 0) & (n != 0)
	{
		if(x>0)	//	if x>0, then sign of x^n is "+"
		{
			ans_sign_flag=0;
			complex=0;
		}
		else
		{
			if(n-(int)n == 0)	//	if n is integer
			{
				complex=0;
				if(abs(n)%2 == 0)	//	if (x<0 & n is even integer), then sign of x^n is "+"
				{
					ans_sign_flag=0;
					x=x*(-1);
				}
				else	//	if (x<0 & n is odd integer), then sign of x^n is "-"
				{
					ans_sign_flag=1;
					x=x*(-1);
				}
			}
			else	//	if (x<0 & n is not an integer), then x^n is a "complex number"
			{
				complex=1;
			}
		}
		
		if(!complex)
		{
			p=n*log(x);
			e_p=1;	//indicates e^p
			term=1;
			i=1;
			//printf("%f\n",p);
			while(fabs(term) > err)
			{
				term=term*p/i;
				e_p=e_p+term;
				i++;
			}
			ans=e_p;
			
			if(ans_sign_flag == 1)	//Changing sign of ans, according to sign flags
			{
				ans=ans*(-1);
			}
		}
		else
		{
			ans=INT_MAX;
		}
	}
	
	return ans;
}

double intPower(long int x, long int n)
{
	long int pow_seq;
	double ans;
	int ans_sign_flag,n_sign_flag;
	
	if(n==0)	//	(-inf < x < inf) & (n = 0)
	{
		ans=1;
	}
	else if(x == 0)	
	{
		if(n>0)	//	(x = 0) & (0 < n < inf)
		{
			ans=0;
		}
		else	//	(x = 0) & (-inf < n < 0)
		{
			ans=INT_MAX;
		}
	}
	else	//	(x != 0) & (n != 0)
	{
		if(n>0)
		{
			n_sign_flag=0;
		}
		else
		{
			n_sign_flag=1;
			n=n*(-1);
		}
		
		if(x>0)	//	if x>0, then sign of x^n is also +
		{
			ans_sign_flag=0;
		}
		else
		{
			if(n%2 == 0)	//	if (x<0 & n is even integer), then sign of x^n is "+"
			{
				ans_sign_flag=0;
				x=x*(-1);
			}
			else	//	if (x<0 & n is odd integer), then sign of x^n is "-"
			{
				ans_sign_flag=1;
				x=x*(-1);
			}
		}
		//printf("%ld__%ld__%d__%d\n",x,n,n_sign_flag,ans_sign_flag);
		
		ans=1;
		pow_seq=x;
		while(n>0)
		{
			if(n%2 == 1)
			{
				ans=ans*pow_seq;
			}
			pow_seq=pow_seq*pow_seq;
			n=n/2;
		}
		
		if(n_sign_flag == 1)	//Changing sign of ans, according to sign flags
		{
			ans=(double)1.0/ans;
		}
		if(ans_sign_flag == 1)	//Changing sign of ans, according to sign flags
		{
			ans=ans*(-1);
		}
	}
	
	return ans;
}
