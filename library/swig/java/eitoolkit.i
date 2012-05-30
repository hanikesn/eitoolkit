%module(directors="1") eitoolkit_java

%javaconst(1);

%include "../common/eitoolkit.i"

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("eitoolkit_java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}
