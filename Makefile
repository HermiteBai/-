all: moyu.c
	clang moyu.c -o moyu
moyu.c:
	mkdir moyu_download
	curl -o moyu.c https://github.com/HermiteBai/Again-you-are-not-paying-attention/blob/master/moyu.c
	echo “./moyu 1” > ./activate.sh
clean:
	rm ./moyu
