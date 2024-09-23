FROM node:18-alpine as cpp-build

RUN apk update && \
    apk add --no-cache \
    build-base=0.5-r3 \
    cmake=3.24.3-r0 \
    docker=27.3.1-r0

WORKDIR /app

COPY ../ChessCore ../ChessEngine ./
COPY ../ChessEngine-bindings/javascript ./ChessEngine-bindings-javascript

WORKDIR /app/ChessEngine-bindings-javascript
RUN ./buildforweb.sh 

FROM cpp-build AS node-build

RUN apk update && \
    apk add --no-cache \
    libstdc++=14.2.0-r2

WORKDIR /app/GameHive 

COPY . .
COPY --from=cpp-build /app/build/ChessEngineJS.js ./app/lib/
RUN npm run build 

FROM node-build AS production 

RUN apk update && \
    apk add --no-cache \
    libstdc++=14.2.0-r2

ENV NODE_ENV=production

WORKDIR /app

RUN addgroup -g 1001 -S nodejs
RUN adduser -S nextjs -u 1001
USER nextjs

COPY --from=builder --chown=nextjs:nodejs /app/GameHive/.next ./.next
COPY --from=builder /app/GameHive/node_modules ./node_modules
COPY --from=builder /app/GameHive/package.json ./package.json
COPY --from=builder /app/GameHive/public ./public

RUN npm ci 

CMD ["npm", "start"]