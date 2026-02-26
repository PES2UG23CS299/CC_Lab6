pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                // Ensure the path matches your repo structure
                sh 'docker build -t backend-app backend' [cite: 367, 611]
            }
        }
        stage('Deploy Backends') {
            steps {
                sh 'docker rm -f backend1 backend2 || true' [cite: 405, 624]
                sh 'docker run -d --name backend1 backend-app' [cite: 407, 625]
                sh 'docker run -d --name backend2 backend-app' [cite: 410]
            }
        }
        stage('Deploy NGINX') {
            steps {
                sh 'docker rm -f nginx-lb || true' [cite: 543, 630]
                // Note: The path below assumes Jenkins workspace structure
                sh "docker run -d --name nginx-lb -p 80:80 -v \$(pwd)/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro nginx" [cite: 546, 634]
            }
        }
    }
}
