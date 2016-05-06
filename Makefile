all: moyu.c
	clang moyu.c -o 摸鱼
moyu.c:
	mkdir moyu_download
	curl -o moyu.c https://github.com/HermiteBai/Again-you-are-not-paying-attention/blob/master/moyu.c
	echo "./摸鱼" > ./activate.sh
clean:
	rm ./摸鱼
