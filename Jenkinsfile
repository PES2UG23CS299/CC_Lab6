pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backends') {
            steps {
                sh 'docker rm -f backend1 backend2 || true'
                sh 'docker run -d --name backend1 backend-app'
                sh 'docker run -d --name backend2 backend-app'
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh 'docker rm -f nginx-lb || true'
                sh "docker run -d --name nginx-lb -p 80:80 -v ${WORKSPACE}/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro nginx"
            }
        }
    }
}

