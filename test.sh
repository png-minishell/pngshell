number=0
while [ $number -lt 100 ]
do
	echo "======================"
	leaks minishell
	((number++))
	sleep 2
done
