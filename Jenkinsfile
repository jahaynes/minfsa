pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        sh 'gcc -Wall -O3 -o ./main *.c *.h'
      }
    }
    stage('run') {
      steps {
        sh 'echo "one two three" | ./main'
      }
    }
  }
}