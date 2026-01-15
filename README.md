# LCdriver
### * 개인 포트폴리오 목적으로 작성한 프로젝트 입니다. *
---
### 실제 센서 대신 가상 센서를 구현하여 유저 공간과 커널 공간 간의 통신 구조를 나타냈습니다.

* Linux kernel 공간에서 동작하는 디바이스 드라이버를 C로 구현하고
  유저 공간(user space)에서 디바이스 파일을 통해 센서 값을 읽습니다.
---
##동작 흐름

* 유저 공간 -> (open) -> /dev/lc -> (read) -> lc_read 실행 -> (kernel 내부 실행) -> 가상 센서값 -> 사용자 복사 후 유저 공간 전달 -> 유저 프로그램에서 센서 값 출력                  

---
## 특징 설명
### character device driver
- open, read, release 구현
- dev/lc 통해 접근

### Virtual Sensor(가상 센서)
- 실제 하드웨어 센서 없이 가상으로 랜덤 값 생성
- 센서 값 -> 커널 내부 변수 -> 유지

### Kernel Timer
- 1초 주기로 센서 값 갱신 
- 레지스터 캐시 개념 학습

### ioctl control
- 센서 on/off 제어
- 제어용 인터페이스 설계