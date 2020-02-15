#!/bin/sh
if [ -n $TERM ]
then
	# Ansi excape color sequences
	RED="\033[1;31m"
	GREEN="\033[0;32m"
	BGREEN="\033[1;32m"
	BLUE="\033[0;34m"
	YELLOW="\033[0;33m"
	PURPLE="\033[0;35m"
	CYAN="\033[0;36m"
	GREY="\033[0;37m"

	# When printed reset the color
	COLRESET="\033[0m"

	# Move the cursor at the begining of the line
	MOVELINE="\033[1A"
	# Erase current line
	CLEARLINE="\033[K"
fi

# check if a program is given as arg
NAME="$HOME/42sh/42sh"

TEST_SHELL='bash --posix'

if [ $2 ]
then
# List of all files in which test are stored
TEST_FILES=$(find $2 -name '*.cmd')
else
TEST_FILES=$(find cmd -name '*.cmd')
fi

FTSH_LOG="42sh_log.tmp"

# Options used for valgrind
LOG_OPT="--log-file=$FTSH_LOG --quiet --leak-check=full"
LOG_OPT=$LOG_OPT" --suppressions=../osxerr.supp"

# Test if the executable exist
if [ -f $NAME -a -x $NAME ]
then
	# if it does run once on valgrind to remove the error valgrind
	# give to freshly compiled program
	# "warning: no debug symbols in executable (-arch x86_64)"
	if [ ! $NOVALGRIND ]
	then
		echo 'exit' | valgrind $NAME > /dev/null 2> /dev/null
	fi
else
	# Check if it isn't a command, for comparing with other shells
	if ! type $NAME > /dev/null
	then
		echo ${RED}[ERR]${COLRESET}"	: $NAME does not exist"
		exit 1
	fi
fi

# Make programs that kill themself
make -C bin/ 1>/dev/null 2>/dev/null
mkdir -p tmp/ $(cd cmd ; find . -type d | sed -e 's/\./res/g')

# Loop over each $FILE in cmd
for FILE in $TEST_FILES
do
	# Get a more 'sexy' version of the $FILE's path
	# ex: cmd/test18.cmd become test18
	SHORTFILE=$(echo $FILE | sed -e 's/^cmd\///g' | sed -e 's/\.cmd$//g')
	echo ${YELLOW}[...]${COLRESET}"	: "${SHORTFILE}${MOVELINE}

	CMPFILE="res/${SHORTFILE}_cmp1.tmp"
	CMPFILE2="res/${SHORTFILE}_cmp2.tmp"
	# Test what result the reference shell gives
	(cd tmp/ ; $TEST_SHELL <../$FILE 1>../$CMPFILE 2>../$CMPFILE2)
	TESTSH_RTN=$?

	OUTFILE="res/${SHORTFILE}_res1.tmp"
	OUTFILE2="res/${SHORTFILE}_res2.tmp"

	rm -f tmp/$FTSH_LOG

	# Test what our shell gives
	if [ ! $NOVALGRIND ]
	then
		(cd tmp/ ; valgrind $LOG_OPT \
			$NAME <../$FILE 1>../$OUTFILE 2>../$OUTFILE2)
		FTSH_RTN=$?
		grep -Ev '^--[0-9]*-- UNKNOWN ' tmp/$FTSH_LOG > tmp/$FTSH_LOG
	else
		(cd tmp/ ; $NAME <../$FILE 1>../$OUTFILE 2>../$OUTFILE2)
		FTSH_RTN=$?
	fi

	# If anything is diffrent
	if diff -q $CMPFILE $OUTFILE > /dev/null \
			&& test -f $CMPFILE2 && test -f $OUTFILE2 \
			&& test $TESTSH_RTN -eq $FTSH_RTN \
			&& test ! -s tmp/$FTSH_LOG
	then
		echo ${CLEARLINE}${GREEN}[OK]${COLRESET}"	: "${SHORTFILE}
	else
		echo ${CLEARLINE}${RED}[KO]${COLRESET}"	: "${SHORTFILE}

		cat $FILE | sed -e "s/^/    /g"

		printf ${GREY}
			diff $CMPFILE $OUTFILE | sed -e "s/^/    /g"
		printf ${PURPLE}
			diff $CMPFILE2 $OUTFILE2 | sed -e "s/^/    /g"
		printf ${CYAN}
			if [ '!' $TESTSH_RTN -eq $FTSH_RTN ]
			then
				echo $TEST_SHELL retuned $TESTSH_RTN | sed -e "s/^/    /g"
				echo $NAME retured $FTSH_RTN | sed -e "s/^/    /g"
			fi
		printf ${BLUE}
			if [ -f tmp/$FTSH_LOG ]
			then
				cat tmp/$FTSH_LOG | sed -e "s/^/    /g"
			fi
		printf ${COLRESET}
	fi
done

# Clear files
rm -rf tmp/
