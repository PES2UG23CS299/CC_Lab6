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
                // Task 4: Run NGINX and mount the local configuration
                sh 'docker rm -f nginx-lb || true'
                sh "docker run -d --name nginx-lb -p 80:80 -v \$(pwd)/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro nginx"
            }
        }
    }
}
