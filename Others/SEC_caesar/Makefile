SRC	=	hex2base64.py \
		xor.py \
		breakSingleXor.py \
		detectSingleXor.py \
		xor2.py \
		breakXor.py \
		AES_ECB.py \
		empty.py \
		AES_CBC.py \
		breakAppendedStringAES_ECB.py \
		changeRoleAES_ECB.py \
		breakAppendedStringAES_ECB2.py \
		insertStringAES_CBC.py \
		CBCOraclePadding.py \

all:
	@i=1; for src in ${SRC}; do \
        file=`printf "challenge%02d" $$i`; \
		cp $$src $$file; \
		chmod +x $$file; \
		echo "cp $$src $$file"; \
        i=`echo $$i + 1 | bc`; \
    done

clean:

fclean:
	@i=1; file=""; while [ $$i -le 14 ]; do \
        file="$$file `printf "challenge%02d" $$i`"; \
        i=`echo $$i + 1 | bc`; \
    done; \
	rm -rf $$file; \
	echo "rm -rf $$file"; \

re: fclean all
