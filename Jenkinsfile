pipeline {
    agent any
    stages {
        stage('Setup Network') {
            steps {
                // Creates network if it doesn't exist
                sh 'docker network create lab6-net || true'
            }
        }
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backends') {
            steps {
                sh 'docker rm -f backend1 backend2 || true'
                // CRITICAL: Backends must be on the same network as Nginx
                sh 'docker run -d --name backend1 --network lab6-net backend-app'
                sh 'docker run -d --name backend2 --network lab6-net backend-app'
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh 'docker rm -f nginx-lb || true'
                sh 'docker run -d --name nginx-lb --network lab6-net -p 80:80 nginx'
                // Wait for Docker DNS to register the new container names
                sleep 5
                sh 'docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf'
                sh 'docker exec nginx-lb nginx -s reload'
            }
        }
    }
}