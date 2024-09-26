#FROM node:18-alpine AS cpp-build

#RUN apk update && \
#    apk add --no-cache \
#    build-base=0.5-r3 \
#    cmake=3.29.3-r0 \
#    python3=3.12.6-r0 \
#    git=2.45.2-r0 

#RUN git clone https://github.com/emscripten-core/emsdk.git

#WORKDIR /emsdk 

#RUN ./emsdk install latest
#RUN ./emsdk activate latest 
#RUN . ./emsdk_env.sh
#RUN ls -la /emsdk/upstream/bin

#ENV PATH /emsdk:/emsdk/upstream/emscripten:$PATH 
#ENV EMSDK /emsdk 
#ENV EMSDK_NODE /emsdk/node/18.20.3_64bit/bin/node

#WORKDIR /app

#COPY ChessCore ./ChessCore/
#COPY ChessEngine ./ChessEngine/
#COPY ChessEngine-bindings/javascript ./ChessEngine-bindings-javascript

#WORKDIR /app/ChessEngine-bindings-javascript

#RUN mkdir -p build/lib
#RUN mkdir build/src

#WORKDIR /app/ChessEngine-bindings-javascript/build

#RUN ["cp", "/app/ChessCore", "./lib", "-r"]
#RUN ["cp", "/app/ChessEngine", "./lib", "-r"]
#RUN ["cp", "/app/ChessEngine-bindings-javascript/src/ChessEngineJS.cpp", "./src"]
#RUN ["cp", "/app/ChessEngine-bindings-javascript/CMakeLists.txt", "."]
#RUN emcmake cmake . -DBUILD_FOR_WEB=1
#RUN make 

#RUN ./buildfordocker.sh 

#FROM cpp-build AS node-build
FROM node:18-alpine AS node-build

RUN apk add --no-cache libc6-compat

WORKDIR /app/GameHive 

COPY ./GameHive-web ./
RUN npm ci 
RUN ls -la
#COPY --from=cpp-build /app/ChessEngine-bindings-javascript/build/ChessEngineJS.js ./app/lib/
RUN npm run build 

FROM node-build AS production 

#RUN apk add --no-cache libc6-compat

ENV NODE_ENV=production

WORKDIR /app

EXPOSE 3000

RUN addgroup -g 1001 -S nodejs
RUN adduser -S nextjs -u 1001
USER nextjs

COPY --from=node-build --chown=nextjs:nodejs /app/GameHive/.next ./.next
COPY --from=node-build /app/GameHive/node_modules ./node_modules
COPY --from=node-build /app/GameHive/package.json ./package.json
COPY --from=node-build /app/GameHive/public ./public

CMD ["npm", "start"]