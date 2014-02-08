如果要发布单个文件，没必要打.a文件，可以直接丢出对应的.o文件即可。
provider工程生成时一个so文件，同时生成o文件

模块发布【只发布one模块】：
	将 /provider/obj/local/armeabi/objs/provider/ 下面的one.o 拷贝到consumer/jni/目录下
	two模块以提供源码，直接将two.c拷贝到consumer/jni下
	
##　也可以将one、two模块以一个.o文件发布， 定义一个three.c内部include所有要发布模块的c文件
