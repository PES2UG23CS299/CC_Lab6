pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                // Task 2: Build the backend application image
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backends') {
            steps {
                // Task 3: Deploy two backend instances for load balancing
                sh 'docker rm -f backend1 backend2 || true'
                sh 'docker run -d --name backend1 backend-app'
                sh 'docker run -d --name backend2 backend-app'
            }
        }
        stage('Deploy NGINX Load Balancer') {
    steps {
        sh 'docker rm -f nginx-lb || true'
        // Using ${WORKSPACE} ensures the path is absolute and correct for the Jenkins container
        sh "docker run -d --name nginx-lb -p 80:80 -v ${WORKSPACE}/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro nginx"
        }
    }
}

