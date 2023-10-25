import prisma from '../prisma'

export default defineEventHandler(async (event) => {
    let postBody = await readBody(event);
    const sensor_data = await prisma.sensor_data.create({data: postBody})
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
