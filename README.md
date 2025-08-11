# Minishell project

---

### 간단 사용 설명서
LinuxOS or MacOS에서 사용
1. make 로 컴파일
2. 리눅스에서 컴파일 오류시  "sudo apt install libreadline-dev" 입력
3. ./minishell 로 실행

---

### 구현한 사용자 기능
	1. redirection [ <, >, >>, << ]
		-> 순서대로  파일 읽기, 쓰기, 이어 쓰기, 사용자 입력 읽기 기능 구현
		ex) < infile cat > outfile
		ex) << eof1 << eof2 << eof3

	2. pipe [ | ]
		ex) [ ls | cat | cat ]

	3. logical operators [ &&, || ]
		ex) export NAME=test_user && echo $NAME || echo "this sentence is not excuted"

	4. shell expansion [ $, $?, * ]
		-> replace environment variable, exit status and wild card.
		ex) echo $PATH
		ex) echo $?
		ex) echo *
		Edge case) export VAR="  o  '  x  " && ech$VAR

	5. signal [ SIGINT, SIGQUIT ] 
		-> ctrl + c, ctrl + \ 
		시그널 핸들러를 구현해서 정상적으로 종료되도록 처리

	6. built-in command: [ cd, pwd, echo, exit, env, export ]
		-> echo만 -n 옵션 추가하고 나머지는 옵션 제외하고 구현

---

### 프로그램 처리 과정
	파싱 부분과 실행 부분으로 나뉜다.

	<파싱부>
	1. 사용자 입력을 한 라인씩 받는다.
	2. 논리연산자를 기준으로 구분해서 트리구조를 생성하고 리프노드는 연결리스트로 문자열 파싱
		-> 여기서는 괄호처리와 문자열 구문의 오류를 검사해서 처리한다.
		ex) "((((echo a b c && (ls && < infile cat | cat | cat > outfile)))))"'
			-> 마지막 ['] single quote는 파싱 오류로 처리

	<실행부>
	1. 파싱된 자료구조를 순회한다.
	2. pipe 존재여부에 따라 로직을 나눈다. (pipe가 있으면 반드시 fork를 뜬다.)
	3. built-in 명령어가 있는지 확인한다. 
	4. shell expansion을 해야하는지 확인한다. ($, $?, * 문자 있는지 확인)
	5. single quote, double quote [", '] 가 있으면 제거한다. (리터럴은 제외)
	6. 나누어진 로직에 따라 순서대로 실행시킨다. 
	7. 마지막으로 실행된 프로세스의 종료 상태를 저장한다.

