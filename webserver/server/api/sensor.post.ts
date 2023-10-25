import {Prisma, PrismaClient} from "@prisma/client";

export default defineEventHandler(async (event) => {
    const prisma = new PrismaClient();
    let postBody = await readBody(event);
    let sensor_entry: Prisma.sensor_dataCreateInput = postBody
    const sensor_data = await prisma.sensor_data.create({data: sensor_entry})
    if (sensor_data) {
        return {
            status: 1,
            message: "Recorded data successfully"
        }
    }
    return {
        status: 0,
        message: "Failed to record data"
    }
});
