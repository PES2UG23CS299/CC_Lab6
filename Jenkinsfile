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
    stage('Deploy NGINX Load Balancer') {
    steps {
        sh 'docker rm -f nginx-lb || true'
        // 1. Run a fresh Nginx container without a volume mount
        sh 'docker run -d --name nginx-lb -p 80:80 nginx'
        // 2. Wait 2 seconds for the container to initialize
        sleep 2
        // 3. Copy your local config file into the running container
        sh 'docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf'
        // 4. Reload Nginx to apply the new configuration
        sh 'docker exec nginx-lb nginx -s reload'
    }
    }
}



