FROM node:18-alpine AS base 

FROM base AS node-build

RUN apk add --no-cache libc6-compat

WORKDIR /app/GameHive 

COPY ./GameHive-web ./
RUN npm ci 
RUN ls -la
RUN npm run build 

FROM base AS production 

ENV NODE_ENV=production

WORKDIR /app

EXPOSE 3000

RUN addgroup -g 1001 -S nodejs
RUN adduser -S nextjs -u 1001

COPY --from=node-build --chown=nextjs:nodejs /app/GameHive/.next/standalone ./.next/standalone 
COPY --from=node-build --chown=nextjs:nodejs /app/GameHive/.next/static ./.next/static 
COPY --from=node-build /app/GameHive/package.json ./package.json
COPY --from=node-build /app/GameHive/public ./public

USER nextjs

CMD ["npm", "start"]