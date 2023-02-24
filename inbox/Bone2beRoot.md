
# Introduction

set up own operating system while implementing ==strict rules.==

login.def
hostnamectl set-hostname 'newname'

# Mandatory
	- Virtualbox 사용
	- signiture.txt file이 최상위 폴더에 있어야 함. 파일에는 가상머신의 가상 디스크 서명을 포함.
	- 데비안 또는 록키 추천(당신이 시스템 뉴비라면 데비안)
	- LVM을 사용하여, 최소한 두개의 encrypted partitions를 만들어라!
	- ssh 서비스 - 4242 포트만을 이용. 보안상 문제 때문에, root를 연결하는 건 금지
		- 몇 가지의 계정을 만들어서 테스트.
	- UFW 방화벽을 사용해서 운영체제를 만들어야 하며 4242 포트만 남겨둬야 함.
	- hostname : your login+42 : 평가 중 변경하게 될 것임.
	- 강력한 비밀번호 규정
		- 30일마다 expire
		- 바꾸고 나서 2일 이내에는 못바꿈
		- 
	- You have to install and configure sudo following strict rules.


https://tonyhan18.tistory.com/201?category=1018635
첫 설치 및 설정 방법(보너스용)

https://m.blog.naver.com/dlatjgns/220031793234
볼륨 축소하기


# 명령어
==lsblk== list block devices (파티션 나눠진 모습 보기)
==sudo== 
	`visudo` sudoers file 보기
`su -` super 유저로 로그인(root)

# 자료 정리
## 운영체제
### Debian vs Rocky

## OS란? [[OS]]
### 하드웨어,  커널, 사용자 프로세스
하드웨어 : 시스템의 토대가 되는 물리적 머신. 
		메모리(ram) / 프로세서 / 중앙 처리 장치(CPU) / 입출력장치 (I/O)

커널 : OS의 핵심. 메모리에 상주하며 CPU에 명령을 내리는 소프트웨어
	**사용자가 system call을 통해 컴퓨터 자원을 사용할 수 있게해주는 자원 관리자**
	사용자 프로세스 (프로세스)
		실행 중인 프로그램으로, 커널이 관리. 커널은 이러한 프로세스 및 서버가 서로 통신할 수 있도록 해줌


## 패키지관리
### 패키지란?
커널 및 라이브러리 버전의 배포판 환경에 맞추어 빌드한 실행파일을 압축한 것

### aptitude / apt 차이
- apt(advanced packaging tool)
	데비안 GNU, 리눅스 배포판 계열에서 소프트웨어를 설치 및 제거
	소스 코드 컴파일을 통하여 소프트웨어 관리를 단순화
	/etc/apt/sources.list 목록에서 해당 패키지 - 종속성 목록과 함께 찾아 자동으로 설치
	직접 소스 목록을 추가할 수도 있고, 업그레이드는 선택적
- aptitude
	apt + GUI 
	rpm 기반 패키지까지 확장됨
- 실 사용에서의 차이점
	사용되지 않는 패키지까지 삭제해줌.
	why-not, why 명령어를 이용해 어떤 동작이 왜 안돼고 되는지를 볼 수 있음
	해결 방법까지 제시


## Apparmor
- 리눅스 커널 보안 모듈 - 실행되는 어플들을 권한을 제한
- CentOS와 같은 제품 및 파생제품은 SELinux, 다른 대부분은 APPArmor를 사용
- 강제적 접근 통제(MAC)를 제공함으로써 전통적인 유닉스 임의적 접근 통제 모델(DAC)을 지원

unix : DAC 임의 접근 통제
시스템 객체에 대한 접근을 사용자나 또는 그룹의 신분을 기준으로 제한하는 방법입니다.

강제 접근 통제(MAC; Mandatory Access Control)는 미리 정해진 정책과 보안 등급에 의거하여 주체에게 허용된 접근 권한과 객체에게 부여된 허용 등급을 비교하여 접근을 통제하는 모델입니다.

# user
### useradd / adduser 차이점
## 보너스 - 파티션을 나누는 이유

### #Cron (시간 기반 잡 스케줄러)

유닉스 계열 OS의 시간 기반 잡 스케줄러이다. 고정된 시간, 날짜, 간격으로 주기적으로 실행하기 위해 cron이 사용된다.
실행 안됨 오류  : 일단 syslog 확인을 위해 install rsyslog 
확인했더니  <span style="background:rgba(240, 200, 0, 0.2)">(CRON) info (No MTA installed, discarding output)</span>
https://cronitor.io/cron-reference/no-mta-installed-discarding-output


### #WordPress
aptitude install lighttpd lighttpd-doc -y
```
aptitude purge lighttpd
aptitude install lighttpd -y
```

-   DB 생성: `CREATE DATABASE wordpress;`
-   계정 생성 및 패스워드 설정: `CREATE USER 'siwolee'@'localhost' IDENTIFIED BY 'Dnlsld11.';`
-   생성한 DB에 대해 생성한 계정에 full access 부여: `GRANT ALL ON wordpress.* TO 'siwolee'@'localhost' IDENTIFIED BY 'Dnlsld11.' WITH GRANT OPTION;`
-   설정을 마침: `FLUSH PRIVILEGES;`
-   종료: `EXIT;`

계속 forbidden 403이 떴던 이유: index.html이 없었음....



https://velog.io/@octo__/Born2beRoot-WordPress-%EA%B5%AC%EC%B6%95





# 유용한 서비스
https://mpjamong.tistory.com/157
https://anonyges.tistory.com/5
https://www.cloudbooklet.com/how-to-install-and-setup-sendmail-on-debian-10/

서버테스트 
`telnet localhost 25`


```
echo -e "To: kimmy.haecho@gmail.com\nSubject: Test1\njdflkjdklfdjfkldj\n" | ssmtp -bm -t -v
```



tlqkf 
# SSMTP