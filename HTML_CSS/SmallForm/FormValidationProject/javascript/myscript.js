    //********************************************************************************//
    //* Name : Sebastian Vieira                                                      *//
    //* Zenit login : int222_151e26                                                  *//
    //********************************************************************************//


    //********************************************************************************//
    //*   Do not modify any statements in detailPaymentCalculation function          *//
    //********************************************************************************//

function detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) {

    //********************************************************************************//
    //*   This function calculates the monthly payment based on the following:       *//
    //*                                                                              *//
    //*               M = P [ i(1 + i)n ] / [ (1 +  i)n - 1]                         *//
    //*                                                                              *//
    //********************************************************************************//
     var paymentError = "";
     var v = mortAmount * 1;
     var d = mortDownPayment * 1;
     var i = mortRate * 1;
     var y = mortAmortization * 1;
     var a = v - d;
         i = i/100/12;
         n = y * 12;
     var f = Math.pow((1+i),n);

     var p = (a * ((i*f)/(f-1))).toFixed(2);

     if (p=="NaN" || p=="Infinity") {
         document.forms[0].payment.value = "";
     }
     else {
           document.forms[0].payment.value = p;
     }

} // End of detailPaymentCalculation function


function validationForPayment() {   

    //********************************************************************************//
    //*   You will need to call the functions that validate the following:           *//
    //********************************************************************************//
    //*        (1)              (2)              (3)             (4)                 *//
    //********************************************************************************//
    //*   Property value  -  Down payment  -  Interest rate -  Amortization          *//
    //********************************************************************************//
    //*   If there are no errors, then call                                          *//
    //*                                                                              *//
    //*      detailPaymentCalculation(...., ......, ......, ......);                 *//
    //*                                                                              *//
    //*   and make sure to pass the four values in the order shown above.            *//
    //*                                                                              *//
    //********************************************************************************//
    //*   If there are errors, simply update the comments area with the message:     *//
    //*   Please complete the form first and then click on Calculate Monthly Payment *//
    //*                                                                              *//
    //********************************************************************************//

	var allErrors = "";
	var error1 = "", error2 = "", error3 = "", error4 = "";
	var ppValue = 0, downPayment = 0, intRate = 0, amort = 0;
	
	error1 = ValidationForAmortization(error1);
	error2 = ValidationForDownPay(error2);
	error3 = ValidationForInterestRate(error3);
	error4 = ValidationForPropValue(error4);
	
	allErrors = error1 + error2 + error3 + error4;
	
	
	if(allErrors !== "")
	{
		document.getElementById('errors').innerHTML = "<p>Please complete the form first and then click on Calculate Monthly Payment</p>";
	}
	else
	{
		ppValue = document.getElementById('propValue').value;
		downPayment = document.getElementById('downPay').value;
		intRate = document.getElementById('intRate').value;
		amort = document.getElementById('amortization').value;
		
		detailPaymentCalculation(ppValue, downPayment, intRate, amort);
	
	
	}
	
	
	
	
} // End of validationForPayment function



function completeFormValidation() {

    //********************************************************************************//
    //*                                                                              *//
    //* This function calls the different functions to validate all required fields  *//
    //*                                                                              *//
    //* Once you have validated all field,                                           *//
    //* determine if any error(s) have been encountered                              *//
    //*                                                                              *//
    //* If any of the required fields are in error:                                  *//
    //*                                                                              *//
    //*    present the client with a list of all the errors in reserved area         *//
    //*         on the form and                                                      *//
    //*          don't submit the form to the CGI program in order to allow the      *//
    //*          client to correct the fields in error                               *//
    //*                                                                              *//
    //*    Error messages should be meaningful and reflect the exact error condition.*//
    //*                                                                              *//
    //*    Make sure to return false                                                 *//
    //*                                                                              *//
    //* Otherwise (if there are no errors)                                           *//
    //*                                                                              *//
    //*    Change the 1st. character in the field called client to upper case        *//
    //*                                                                              *//
    //*    Change the initial value in the field called jsActive from OFF to ON      *//
    //*                                                                              *//
    //*    Make sure to return true in order for the form to be submitted to the CGI *//
    //*                                                                              *//
    //********************************************************************************//
	var allErrorMessages = "";
	var error1 = "", error2 = "", error3 = "", error4 = "", error5 = "", error6 = "", error7 = "", error8 = "", error9 = "", error10 = "", error11 = "";
	var i;
	var changeJs;
	var clientName, clientLetter, clientAfter;
	
	error1 = ValidationForAmortization(error1);
	error2 = ValidationForInterestRate(error2);
	error3 = ValidationForMortYear(error3);
	error4 = ValidationForMortMonth(error4);
	error5 = ValidationForClientId(error5);
	error6 = ValidationForClientName(error6);
	error7 = ValidationForPropValue(error7);
	error8 = ValidationForDownPay(error8);
	error9 = ValidationForLocation(error9);
	error10 = ValidationForIncome(error10);
	error11 = ValidationForPropertyTp(error11);
	
	 allErrorMessages = error1 + error2 + error3 + error4 + error5 + error6 + error7 + error8 + error9 + error10 + error11; 
	
	
	if(allErrorMessages !== "")
	{
		ShowError(allErrorMessages);
		return false;
	}
	else
	{
		clientName = document.getElementById('client').value;
		clientLetter = clientName.substr(0, 1);
		clientLetter = clientLetter.toUpperCase();
		clientAfter = clientName.substr(1);
		clientName = clientLetter + clientAfter;
		document.getElementById('client').value = clientName;
		validationForPayment();
		document.getElementById('jsActive').value = "Y";
		return true;
	}

} // End of completeFormValidation

//******************************************************//
/*				Show Error Message				*/
//******************************************************//
function ShowError(message)  
{
	document.getElementById("errors").innerHTML = message;
}
//******************************************************//
/*				Income Validation 					*/
//******************************************************//
function ValidationForIncome(incomeMessage)  
{

	var selectIncome = document.mortgage.income.selectedIndex;
	
	if(selectIncome === -1)
	{
		incomeMessage = "<p>Please select one of the Income Range options</p>";
		return incomeMessage;
	}
	else
	{
		return incomeMessage;
	}
}
//******************************************************//
/*				Location Validation					*/
//******************************************************//
function ValidationForLocation(locationMessage)  
{
	
	var selectLocation = document.mortgage.propLocation.selectedIndex;
	
	if(selectLocation === -1)
	{
		locationMessage = "<p>Please select one of the Location options</p>";
		return locationMessage;
	}
	else
	{
		return locationMessage;
	}
}
//******************************************************//
/*				Property Validation					*/
//******************************************************//
function ValidationForPropertyTp(propertyMessage) 
{
	
	var radioNo = document.mortgage.propDetails.length;
	var i, result;
	
	for(i = 0; i < radioNo; i++)
	{
		if(document.mortgage.propDetails[i].checked === true)
		{
			result = 1;
			break;
		}
		else
		{
			result = 0;
		}
	}
	if(result === 1)
	{
		return propertyMessage;	
	}
	else
	{
		propertyMessage = "<p>Please pick one of the Property types</p>";
		return propertyMessage;
	}
}
//******************************************************//
/*				Client ID Validation					*/
//******************************************************//
function ValidationForClientId(UserIdMessage)  
{
	var i;
	var userValue = document.getElementById("userId").value;
	userValue = userValue.trim();
	var userLength = userValue.length;
	var counter = 0, counter2 = 0;
	var sumLeft = 0, sumRight = 0;
	
	if(userLength === 0)
	{
		UserIdMessage = "<p>You must enter a value for Client ID</p>";
	}
	else if(userLength < 10)
	{
		UserIdMessage = "<p>Client ID must contain 10 values</p>";
	}
	else if(userValue[4] !== "-")
	{
		UserIdMessage = "<p>Position 5 in Client ID must be a hyphen(-)</p>";
	}
	
	for(i = 0; i < 4; i++)
	{
			if(userValue.charCodeAt(i) >= 65 && userValue.charCodeAt(i) <= 122)
			{
				UserIdMessage = "<p>There must be four numeric digits before the hyphen in the Client ID</p>";
				counter++;
			}
	}
	
	for(i = 5; i < 10; i++)
	{
		if(userValue.charCodeAt(i) >= 65 && userValue.charCodeAt(i) <= 122)
			{
				UserIdMessage = "<p>There must be four numeric digits after the hyphen in the Client ID</p>";
				counter2++;
			}
	}
	
	if(counter >= 1 && counter2 >= 1)
	{
		UserIdMessage = "<p>There must be four numeric digits before and after the hyphen in the Client ID</p>";
	}
	
	if(UserIdMessage === "")
	{
		for(i = 0; i < 4; i++)
		{
			sumLeft += eval(Number(userValue[i]));
		}
		
		for(i = 5; i < 10; i++)
		{
			sumRight += eval(Number(userValue[i]));
		}
		
		if(sumRight <= 0 && sumLeft <= 0)
		{
			UserIdMessage = "<p>The numbers on both the left and right side of the hyphen(-) must be greater than zero(0) in the Client ID</p>";
		}
		else if(sumRight <= 0)
		{
			UserIdMessage = "<p>The numbers on the right side of the hyphen must be greater than zero(0) in the Client ID</p>";
		}
		else if(sumLeft <= 0)
		{
			UserIdMessage = "<p>The numbers on the left side of the hyphen must be greater than zero(0) in the Client ID</p>";
		}
		
		
		if(sumLeft > 0 && sumRight > 0)
		{
			sumLeft = eval(sumLeft * 2 + 1);
			if(sumLeft !== sumRight)
			{
				UserIdMessage = "<p>The sum of the numbers to the right of the hyphen (-) must be (double + 1) the sum of the numbers to the left of the hyphen (-) in the Client ID</p>";
				
			}
		}
		
	}
	
	return UserIdMessage;
}
//******************************************************//
/*				Client Name Validation 					*/
//******************************************************//
function ValidationForClientName(clientMessage)
{
	var clientValue = document.getElementById('client').value;
	var clientLengthTrim = clientValue.trim();
	var clientLength = clientLengthTrim.length;
	var i, wordcount = 0;
	var asp = clientValue.indexOf("'");
	var hyp = clientValue.indexOf("-");
	var symbol1 = 0, symbol2 = 0;
	
	if(clientLength === 0)
	{
		clientMessage = "<p>Client Name cannot be empty</p>";
	}
	
	if(clientLength > 0)
	{

			for(i = 0; i < 3; i++)
			{
				if(clientValue.charCodeAt(i) >= 65 && clientValue.charCodeAt(i) <= 122)
				{
					wordcount++;
				}
				
			}
		
			if(wordcount != 3)
			{
				clientMessage = "<p>There must be three alphabetic characters in the first three positions of the Client name</p>";
			}
			
		
			if(wordcount === 3)
			{
				for(i = 0; i < clientLength; i++)
				{
					if(clientValue.charCodeAt(i) >= 48 && clientValue.charCodeAt(i) <= 57)
					{
						clientMessage = "<p>The Client Name must only contain alphabetic characters and an option for one apostrophe (') and one hyphen (-)</p>";
					}
				
					if(clientValue.charCodeAt(i) === 39)
					{
						symbol1++;
					}
				
					if(clientValue.charCodeAt(i) === 45)
					{
						symbol2++;
					}
				}
			
				if(symbol1 >= 2 && symbol2 >= 2)
				{
					clientMessage = "<p>You are only allowed to use one apostrophe (') and one hyphen (-) in the Client Name</p>";
				}
				else if(symbol1 >= 2)
				{
					clientMessage = "<p>You are only allowed one apostrophe (') in the Client Name</p>";
				}
				else if(symbol2 >= 2)
				{
					clientMessage = "<p>You are only allowed one hyphen (-) in the Client Name</p>";
				}
				
				if(clientValue.charCodeAt(clientLength - 1) === 39 || clientValue.charCodeAt(clientLength - 1) === 45)
				{
					clientMessage = "<p>There cannot be an apostrophe (') or a hyphen (-) and the end of the Client name</p>";
				}
			
			
				if(hyp - 1 == asp || hyp + 1 == asp)
				{
					clientMessage = "<p>The apostrophe (') and the hyphen (-) cannot be next to each other</p>";
				}
			}
		
	
	}
	return clientMessage;
}
	

//******************************************************//
/*				Validation for Property Value			*/
//******************************************************//
function ValidationForPropValue(propValueMessage)
{
	var ppValue= document.getElementById('propValue').value;
	ppValue = ppValue.trim();
	var propLength = ppValue.length;
	var downPay = document.getElementById('downPay').value;
	var i;
	var result;
	
	if(propLength === 0)
	{
		propValueMessage = "<p>You must enter a value for the Property Value</p>";
	}
	
	if(propLength > 0)
	{
		for(i = 0; i < propLength; i++)
		{
			if(ppValue.charCodeAt(i) < 48 || ppValue.charCodeAt(i) > 57)
			{
				propValueMessage = "<p>The property value should be a whole number that is positive</p>";
			}
		}
		
		if(ppValue < 50000)
		{
			propValueMessage = "<p>The Property Value cannot be lower than 50000</p>";
		}
		
		if(propValueMessage === "")
		{
			result = eval(ppValue - downPay);
		
			if(result < 65000)
			{
				propValueMessage = "<p>The property value must be at least 65,000 dollars more than the down payment</p>";
			}
			
			result = eval(propValue * 0.10);
			
			if(downPay < result)
			{
				propValueMessage = "<p>Property Value must be at least 10% of the down payment</p>";
			}	
		}
	}
	
	return propValueMessage;
}
//******************************************************//
/*				Validation for Down Payment				*/
//******************************************************//
function ValidationForDownPay(downPayMessage)
{
	
	var downPay = document.getElementById('downPay').value;
	var propValue = document.getElementById('propValue').value;
	downPay = downPay.trim();
	var downLength = downPay.length;
	var i;
	var result;
	
	if(downLength === 0)
	{
		downPayMessage = "<p>You must enter a value for the Down Payment</p>";
	}
	
	if(downLength > 0)
	{
		for(i = 0; i < downLength; i++)
		{
			if(downPay.charCodeAt(i) < 48 || downPay.charCodeAt(i) > 57)
			{
				downPayMessage = "<p>The down payment should be a whole and positive number</p>";
			}
		}
		
		if(downPayMessage === "")
		{
			result = eval(propValue * 0.10);
			
			if(downPay < result)
			{
				downPayMessage = "<p>The down payment must be at least 10% of the property value</p>";
			}				
		}
	}
	
	
	return downPayMessage;
}
//******************************************************//
/*				Validation for Mortgage Year			*/
//******************************************************//
function ValidationForMortYear(mortYearMessage)
{
	
	var mortValue = document.getElementById('mortYear').value;
	mortValue = mortValue.trim();
	var mortLength = mortValue.length;
	var i;
	var date = new Date();
	var Year = date.getFullYear();
	
	if(mortLength === 0)
	{
		mortYearMessage = "<p>The Mortgage Year cannot be empty</p>";
	}
	else if (mortLength > 1 && mortLength < 4)
	{
		mortYearMessage = "<p>The Mortgage Year must be a 4 digit number</p>";
	}
	
	if(mortLength === 4)
	{
		for(i = 0; i < mortLength; i++)
		{
			if(mortValue.charCodeAt(i) < 48 || mortValue.charCodeAt(i) > 57)
			{
				mortYearMessage = "<p>The Mortgage Year must only be numeric</p>";
				break;
			}
		}
		
		if(mortValue < Year || mortValue > Year + 1)
		{
			mortYearMessage = "<p>The Mortgage Year must be equal to the current year or 1 year greater</p>";
		}
	}
	
	return mortYearMessage;
}
//******************************************************//
/*				Validation for Mortgage Month			*/
//******************************************************//
function ValidationForMortMonth(mortMonthMessage)
{

	var mortMonValue = document.getElementById('mortMonth').value;
	mortMonValue = mortMonValue.trim();
	var mortMonLength = mortMonValue.length;
	var i; 
	var date = new Date();
	var Month = date.getMonth() + 1;
	
	if(mortMonLength === 0)
	{
		mortMonthMessage = "<p>The Mortgage Month cannot be empty</p>";
	}
	
	
	if(mortMonLength > 0)
	{
		for(i = 0; i < mortMonLength; i++)
		{
			if(mortMonValue.charCodeAt(i) < 48 || mortMonValue.charCodeAt(i) > 57)
			{
				mortMonthMessage = "<p>The Mortgage Month should be numeric</p>";
				break;
			}
		}
		
		if(mortMonValue > 12 || mortMonValue < 1)
		{
			mortMonthMessage = "<p>The Mortgage Month should be between 1 - 12</p>";
		}
		else if(mortMonValue < Month || mortMonValue > Month + 1)
		{
			mortMonthMessage = "<p>The Mortgage Month must be equal to the current month or 1 month greater</p>";
		}
		
	}
	
	return mortMonthMessage;
}
//******************************************************//
/*				Validation for Interest Rate			*/
//******************************************************//
function ValidationForInterestRate(intRateMessage)
{
	var intRateValue = document.getElementById('intRate').value;
	intRateValue = intRateValue.trim();
	var intRateLength = intRateValue.length;
	var i;
	var periodCount = 0;
	
	if(intRateLength === 0)
	{
		intRateMessage = "<p>The Interest Rate must contain a value</p>";
	}
	
	if(intRateLength > 0)
	{
		for(i = 0; i < intRateLength; i++)
		{
			if(intRateValue.charCodeAt(i) < 48 || intRateValue.charCodeAt(i) > 57)
			{
				intRateMessage = "<p>The Interest rate must be a numeric value</p>";
			}
			
			if(intRateValue.charAt(i) === ".")
			{
				periodCount++;
			}
			
		}
		
		if(intRateValue.indexOf('.') === 1 || intRateValue.indexOf('.') === 2)
			{
				intRateMessage = "";
			}
		
		if(intRateValue < 2 || intRateValue < 2.000 && intRateValue > 11 || intRateValue > 11.000 || periodCount > 1)
		{
			intRateMessage = "<p>The Interest Rate must be between 2 - 11 or 2.000 - 11.000 and in this format</p>";
		}
		
	}
	
	return intRateMessage;
}
//******************************************************//
/*				Validation for Amortization		 		*/
//******************************************************//
function ValidationForAmortization(amortMessage)
{
	var amortValue = document.getElementById('amortization').value;
	amortValue = amortValue.trim();
	var amortLength = amortValue.length;
	var i;
	
	if(amortLength === 0)
	{
		amortMessage = "<p>You must enter a value for Amortization</p>";
	}
	if( amortLength > 0)
	{
		for(i = 0; i < amortLength; i++)
		{
			if(amortValue.charCodeAt(i) < 48 || amortValue.charCodeAt(i) > 57)
			{
				amortMessage = "<p>The Mortgage Amortization can only be numeric</p>";
			}
		}
	
		if(amortValue < 5 || amortValue > 20)
		{
			amortMessage = "<p>The Amortization can only be between 5 - 20 or 05 - 20 inclusive</p>";
		}
	}
	
	return amortMessage;
}		
