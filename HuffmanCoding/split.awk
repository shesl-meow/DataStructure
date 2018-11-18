#/bin/awk -f

BEGIN{
	RS = "==================="; 
	num = 0;
}

{
	filename= "./data/"num".txt";
	print $0 > filename;
	num += 1;
}
