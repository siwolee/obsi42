
# 라이브러리 image not found
```sh
dyld: Library not loaded: libmlx.dylib
  Referenced from: /Users/siwolee/minirt/./a.out
  Reason: image not found
```

![[Screen Shot 2023-04-08 at 4.01.03 PM.png]]
참고한 페이짚 :
https://stackoverflow.com/questions/17703510/dyld-library-not-loaded-reason-image-not-found


### 해결방법 1 : otool을 통해 라이브러리 경로 확인 후 수동으로 경로를 바꿔주기
http://rette.iruis.net/2019/11/%EB%A7%A5%EC%97%90%EC%84%9C-%EB%8F%99%EC%A0%81-%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC-%EC%B0%B8%EC%A1%B0%EB%AC%B8%EC%A0%9C-reason-image-not-found/


실패