# [minishell] Project Rule

# GIT/GITHUB

## Branch

[우린 Git-flow를 사용하고 있어요 | 우아한형제들 기술블로그](https://techblog.woowahan.com/2553/)

### master

이름 → `master`

- `version` 별 배포 브랜치

### develop

이름 → `develop`

- 개발 진행 브랜치

### feature

이름 → `feature_[기능명]`

- 개발 브랜치에서 분화되어 각 기능 구현마다 `feature branch`를 구성
- 기능 완성 이후 `develop branch`에 `merge`

## PR은 필수

- `local git repository` 에서 작업 후  `remote repository` 로 바로 올리지 말 것. 반드시 PR 날려서 해당 작업을 서로 검증하고 코드 리뷰하는 과정을 추가하자.
- 첫 협업 과제이기 때문에 체계적인 관리를 위함 (시간은 오래걸리겠지만…)
- PR 날릴 때는 반드시 아래 코딩 컨벤션을 지킨 코드만 `Merge`를 허가하자.

## Issue 적극적 활용

- 비록 룸메이트라서 함께 늘 있지만, 문제가 발생하면 해당 탭을 적극적으로 활용하여 기록해두자.

[[Git] Github 이슈, 라벨, 마일스톤 기능 및 사용법](https://hbase.tistory.com/211)

[왜 나만 몰라? - 협업을 위한 깃허브 이슈 작성하기](https://velog.io/@junh0328/%ED%98%91%EC%97%85%EC%9D%84-%EC%9C%84%ED%95%9C-%EA%B9%83%ED%97%88%EB%B8%8C-%EC%9D%B4%EC%8A%88-%EC%9E%91%EC%84%B1%ED%95%98%EA%B8%B0)

# Coding convention

기본적으로 `norminette`를 준수한다.

## 클린코드

### 함수

- 함수명은 해당 함수의 동작을 명확하게 표현해야한다.
    - `do_something` 과 같이 `동사 + something`  형태를 가진다.
- 함수는 최대한 모듈화.
    - 함수 내에 `while loop`가 중첩되지 않도록 한다. 만약 `while loop`가 중첩된다면 해당 부분을 따로  모듈화.
    - 상위로 올라가는 함수일 수록 글을 읽는 느낌으로 함수의 나열이 되도록 해야한다.
        - 로직 이해에 큰 도움이 된다.
- 함수의 매개 변수는 **가능한 한 2개 이하**. 3개 이상이 된다면 무언가 복잡하게 작성하고 있는 것.
- `void` 반환형의 함수는 되도록 지양한다. 반환형을 사용하지 않더라도 `t_status`와 같은 형태로 해당 함수의 결과를 반환하도록 하자.
- 서로 다른 파일에서 사용하는 함수의 경우 반드시 `static` 형태가 아닌 별도의 함수 파일을 구성하자.

### 변수

- 변수명은 해당 변수의 의미를 정확히 담을 수 있도록 한다. (줄임말 지양할 것)
    - `n_philosopher` → X
    - `number_of_philosophers` → O
- `index` 를 다루는 정수형의 경우 다음과 같이 정의한다.
- `idx_[index target]`
    - example : `idx_philosopher`

### 변수 선언 및 할당

- `const` 의 경우 가장 상위에 위치해야한다.
- 타입명이 긴 변수가 위에 위치하도록 작성한다.
- 변수의 할당은 반드시 사용 시점 직전에 한다.

### 상수

- 코드의 모든 상수는 숫자 그대로가 아닌 해당 상수가 의미하는 바를 정확하게 표기한다.
- 할당해야하는 상수가 아닌 아래 예시와 같이 정해진 상수는 대문자로 `#define`하도록 한다.
- 예시)
    
    ```jsx
    /* 잘못된 예시 */
    pid = fork()
    if (pid == 0) // child
    ...
    else // parent
    ...
    ```
    
    ```jsx
    /* 올바른 예시 */
    pid = fork()
    if (pid == CHILD_PROCESS_PID)
    ...
    else
    ...
    ```
    

### 주석

- 변수명과 함수명을 통해서 주석이 필요없는 코드를 최대한 작성하자.

### 구조체

- 구조체명 또한 해당 구조체가 의미하는 바를 명확하게 표시해야한다.

### type

- 특별한 의미를 갖는 경우, `typedef` 를 통해서 `type`를 명시적으로 선언한다.
- `t_bool` : `bool` 타입 대체
    - `0` == `FALSE`
    - `1` == `TRUE`
- `t_status` : 함수의 상태값을 전달
    - `0` == `SUCCESS`
    - `-1` == `FAILED`

## Error Handling

### C library 내장 함수

- `fork()`, `open()` 등과 같이 내장 함수의 경우 반드시 사용 이후 반환값을 확인한다.
- 위와 같은 함수의 경우 `errno` 또한 세팅되므로, 이 때 `exit`과 `perror`를 통해서 적절히 프로그램이 종료되도록 유도한다.
- 대부분 `-1`, `NULL` 등을 통해서 에러 상태를 반환하므로 이에 대해서 별도로 `failed case`를 `define` 해둔다.

### 사용자 정의 함수

- 사용자 정의 함수 내에서 예외 경우가 발생하는 경우 통일성을 위해 `-1` 을 반환하는 것을 규칙으로 한다. 이렇게 상태를 반환하는 함수의 경우 반환형은 `t_status`가 될 것이다.
- 위와 같이 상태 반환값이 있는 함수의 경우 반드시 error handling을 위해서 검사한다.
